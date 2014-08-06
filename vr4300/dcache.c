//
// vr4300/dcache.c: VR4300 instruction cache.
//
// CEN64: Cycle-Accurate Nintendo 64 Simulator.
// Copyright (C) 2014, Tyler J. Stachecki.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#include "common.h"
#include "vr4300/dcache.h"

static inline struct vr4300_dcache_line* get_line(
  struct vr4300_dcache *dcache, uint64_t vaddr);
static inline const struct vr4300_dcache_line* get_line_const(
  const struct vr4300_dcache *dcache, uint64_t vaddr);

static inline uint32_t get_tag(const struct vr4300_dcache_line *line);
static void invalidate_line(struct vr4300_dcache_line *line);
static bool is_dirty(const struct vr4300_dcache_line *line);
static bool is_valid(const struct vr4300_dcache_line *line);
static void set_clean(struct vr4300_dcache_line *line);
static void set_dirty(struct vr4300_dcache_line *line);
static void set_tag(struct vr4300_dcache_line *line, uint32_t tag);
static void validate_line(struct vr4300_dcache_line *line, uint32_t tag);

// Returns the line for a given virtual address.
struct vr4300_dcache_line* get_line(
  struct vr4300_dcache *dcache, uint64_t vaddr) {
  return dcache->lines + (vaddr >> 4 & 0x1FF);
}

// Returns the line for a given virtual address.
const struct vr4300_dcache_line* get_line_const(
  const struct vr4300_dcache *dcache, uint64_t vaddr) {
  return dcache->lines + (vaddr >> 4 & 0x1FF);
}

// Returns the physical tag associated with the line.
uint32_t get_tag(const struct vr4300_dcache_line *line) {
  return line->metadata >> 12;
}

// Invalidates the line, but leaves the physical tag untouched.
void invalidate_line(struct vr4300_dcache_line *line) {
  line->metadata &= ~0x1;
}

// Returns true if the line is valid, otherwise returns false.
bool is_dirty(const struct vr4300_dcache_line *line) {
  return (line->metadata & 0x2) == 0x2;
}

// Returns true if the line is valid, otherwise returns false.
bool is_valid(const struct vr4300_dcache_line *line) {
  return (line->metadata & 0x1) == 0x1;
}

// Sets the state of the line to clean.
void set_clean(struct vr4300_dcache_line *line) {
  line->metadata &= ~0x2;
}

// Sets the state of the line to dirty.
void set_dirty(struct vr4300_dcache_line *line) {
  line->metadata |= 0x2;
}

// Sets the tag of the specified line, retaining current valid bit.
void set_tag(struct vr4300_dcache_line *line, uint32_t tag) {
  line->metadata = (tag << 12) | (line->metadata & 0x1);
}

// Sets the line's physical tag and validates the line.
static void validate_line(struct vr4300_dcache_line *line, uint32_t tag) {
  line->metadata = (tag << 12) | 0x1;
}

// Fills an instruction cache line with data.
void vr4300_dcache_fill(struct vr4300_dcache *dcache,
  uint64_t vaddr, uint32_t paddr, const void *data) {
  struct vr4300_dcache_line *line = get_line(dcache, vaddr);

  memcpy(line->data, data, sizeof(line->data));
  validate_line(line, paddr >> 4);
  set_clean(line);
}

// Returns the tag of the line associated with vaddr.
uint32_t vr4300_dcache_get_tag(const struct vr4300_dcache_line *line) {
  return get_tag(line);
}

// Initializes the instruction cache.
void vr4300_dcache_init(struct vr4300_dcache *dcache) {
}

// Invalidates an instruction cache line (regardless if hit or miss).
void vr4300_dcache_invalidate(struct vr4300_dcache *dcache, uint64_t vaddr) {
  struct vr4300_dcache_line *line = get_line(dcache, vaddr);

  invalidate_line(line);
}

// Invalidates an instruction cache line (only on a hit).
void vr4300_dcache_invalidate_hit(struct vr4300_dcache *dcache,
  uint64_t vaddr, uint32_t paddr) {
  struct vr4300_dcache_line *line = get_line(dcache, vaddr);
  uint32_t ptag = get_tag(line);

  if (ptag == (paddr >> 4) && is_valid(line))
    invalidate_line(line);
}

// Probes the instruction cache for a matching line.
const struct vr4300_dcache_line* vr4300_dcache_probe(
  const struct vr4300_dcache *dcache, uint64_t vaddr, uint32_t paddr) {
  const struct vr4300_dcache_line *line = get_line_const(dcache, vaddr);
  uint32_t ptag = get_tag(line);

  // Virtually index, and physically tagged.
  return (ptag == (paddr >> 4) && is_valid(line))
    ? line
    : NULL;
}

// Sets the physical tag associated with the line.
void vr4300_dcache_set_tag(struct vr4300_dcache *dcache,
  uint64_t vaddr, uint32_t tag) {
  struct vr4300_dcache_line *line = get_line(dcache, vaddr);

  set_tag(line, tag);
}

// Returns the line if it's dirty and valid.
// Call before replacement of writeback entry.
struct vr4300_dcache_line *vr4300_dcache_should_flush_line(
  struct vr4300_dcache *dcache, uint64_t vaddr) {
  struct vr4300_dcache_line *line = get_line(dcache, vaddr);

  return is_dirty(line) && is_valid(line)
    ? line : NULL;
}

// Writes back the block if the line is valid, then invalidates the line.
void vr4300_dcache_wb_invalidate(struct vr4300_dcache *dcache, uint64_t vaddr) {
  struct vr4300_dcache_line *line = get_line(dcache, vaddr);

  // TODO: Writeback.
  if (is_valid(line))
    invalidate_line(line);
}

