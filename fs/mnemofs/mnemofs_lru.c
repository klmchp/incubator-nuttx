/****************************************************************************
 * fs/mnemofs/mnemofs_lru.c
 * LRU cache of mnemofs.
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * the BSD-3-Clause license:
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2024 Saurav Pal
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * LRU (Least Recently Used) cache takes in all the changes the user wants
 * to do to the on-flash storage, and stores them in memory. When a
 * significant amount of changes are accumulated, the LRU writes the new
 * information to the flash.
 *
 * LRU is a kernel list of nodes. Each node represents a CTZ list. Each node
 * contains a kernel list of changes requested for the CTZ list, called as
 * deltas.
 *
 * When LRU is full the last node is flushed (it can be explicitly flushed as
 * well) and all the changes are written at once on the flash, and the new
 * location is noted down in the journal, and an entry for the location
 * update is added to the LRU for the parent.
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/kmalloc.h>
#include <nuttx/list.h>
#include <sys/param.h>

#include "mnemofs.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int mfs_lru_ctzflush(FAR struct mfs_sb_s * const sb,
                    FAR struct mfs_path_s * const path, const mfs_t depth,
                    const mfs_t ctz_sz)
{
  /* TODO */

  return OK;
}

int mfs_lru_del(FAR struct mfs_sb_s * const sb, const mfs_t data_off,
                mfs_t bytes, mfs_t ctz_sz,
                FAR struct mfs_path_s * const path, const mfs_t depth)
{
  /* TODO */

  return OK;
}

int mfs_lru_wr(FAR struct mfs_sb_s * const sb, const mfs_t data_off,
              mfs_t bytes, mfs_t ctz_sz, FAR struct mfs_path_s * const path,
              const mfs_t depth, FAR const char *buf)
{
  /* TODO */

  return OK;
}

int mfs_lru_rdfromoff(FAR struct mfs_sb_s * const sb, const mfs_t data_off,
                      FAR struct mfs_path_s * const path, const mfs_t depth,
                      FAR char *buf, const mfs_t buflen)
{
  /* TODO */

  return OK;
}

void mfs_lru_init(FAR struct mfs_sb_s * const sb)
{
  /* TODO */
}

void mfs_lru_updatedsz(FAR struct mfs_sb_s * const sb,
                      FAR const struct mfs_path_s * const path,
                      const mfs_t depth, mfs_t *n_sz)
{
  /* TODO */
}