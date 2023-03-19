//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// table_heap.h
//
// Identification: src/include/storage/table/table_heap.h
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <mutex>  // NOLINT
#include <optional>
#include <utility>

#include "buffer/buffer_pool_manager.h"
#include "common/config.h"
#include "recovery/log_manager.h"
#include "storage/page/table_page.h"
#include "storage/table/table_iterator.h"
#include "storage/table/tuple.h"

namespace bustub {

/**
 * TableHeap represents a physical table on disk.
 * This is just a doubly-linked list of pages.
 */
class TableHeap {
  friend class TableIterator;

 public:
  ~TableHeap() = default;

  /**
   * Create a table heap without a transaction. (open table)
   * @param buffer_pool_manager the buffer pool manager
   * @param first_page_id the id of the first page
   */
  explicit TableHeap(BufferPoolManager *bpm);

  /**
   * Insert a tuple into the table. If the tuple is too large (>= page_size), return std::nullopt.
   * @param meta tuple meta
   * @param tuple tuple to insert
   * @return rid of the inserted tuple
   */
  auto InsertTuple(const TupleMeta &meta, const Tuple &tuple) -> std::optional<RID>;

  /**
   * Insert a tuple into the table. If the tuple is too large (>= page_size), return false.
   * @param meta new tuple meta
   * @param[out] rid the rid of the inserted tuple
   */
  void UpdateTupleMeta(const TupleMeta &meta, RID rid);

  /**
   * Read a tuple from the table.
   * @param rid rid of the tuple to read
   * @param tuple output variable for the tuple
   * @return the tuple
   */
  auto GetTuple(RID rid) -> std::pair<TupleMeta, Tuple>;

  /** @return the iterator of this table */
  auto MakeIterator() -> TableIterator;

  /** @return the id of the first page of this table */
  inline auto GetFirstPageId() const -> page_id_t { return first_page_id_; }

 private:
  BufferPoolManager *bpm_;
  page_id_t first_page_id_{INVALID_PAGE_ID};

  std::mutex latch_;
  page_id_t last_page_id_{INVALID_PAGE_ID}; /* protected by latch_ */
};

}  // namespace bustub
