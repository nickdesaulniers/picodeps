#include <string>
#include "archive.h"
#include "archive_entry.h"
#include "tarball.h"

Tarball::Tarball (const std::string& url) {
  this->location = url;
}

static int copy_data (archive *ar, struct archive *aw) {
  int r;
  const void *buff;
  size_t size;
  off_t offset;

  for (;;) {
    r = archive_read_data_block(ar, &buff, &size, &offset);
    if (r == ARCHIVE_EOF) {
      return (ARCHIVE_OK);
    }
    if (r < ARCHIVE_OK) {
      return (r);
    }
    r = archive_write_data_block(aw, buff, size, offset);
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "%s\n", archive_error_string(aw));
      return (r);
    }
  }
}

static void rewrite_subdir (archive_entry* entry, const std::string& dirname) {
  const auto old_path = std::string { archive_entry_pathname(entry) };
  const auto new_path = dirname + "/" + old_path;
  archive_entry_set_pathname(entry, new_path.c_str());
}

int Tarball::install () {
  archive_entry *entry;
  int r;

  archive* a = archive_read_new();
  archive_read_support_format_all(a);
  archive_read_support_filter_all(a);

  archive* ext = archive_write_disk_new();
  const int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM |
    ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
  archive_write_disk_set_options(ext, flags);
  archive_write_disk_set_standard_lookup(ext);

  const std::string subdir = "deps";
  const std::string filename = subdir + "/" + basename(this->location);
  printf("Unpacking archive %s\n", filename.c_str());
  if ((r = archive_read_open_filename(a,filename.c_str(), 10240))) {
    fprintf(stderr, "Error opening archive:\n%s\n", archive_error_string(a));
    return -1;
  }
  for (;;) {
    r = archive_read_next_header(a, &entry);
    if (r == ARCHIVE_EOF) {
      break;
    }
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "%s\n", archive_error_string(a));
    }
    if (r < ARCHIVE_WARN) {
      return -1;
    }
    rewrite_subdir(entry, subdir);
    r = archive_write_header(ext, entry);
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "%s\n", archive_error_string(ext));
    } else if (archive_entry_size(entry) > 0) {
      r = copy_data(a, ext);
      if (r < ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(ext));
      }
      if (r < ARCHIVE_WARN) {
        return -1;
      }
    }
    r = archive_write_finish_entry(ext);
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "%s\n", archive_error_string(ext));
    }
    if (r < ARCHIVE_WARN) {
      return -1;
    }
  }
  archive_read_close(a);
  archive_read_free(a);
  archive_write_close(ext);
  archive_write_free(ext);

  return 0;
};

