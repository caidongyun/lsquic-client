/* Copyright (c) 2017 - 2018 LiteSpeed Technologies Inc.  See LICENSE. */
/*
 * lsquic_spi.h - SPI: Stream Priority Iterator
 *
 * SPI purposefully does not support switching stream priorities while
 * iterator is active, because this puts iteration termination outside
 * of our control.  One can imagine (admittedly theoretical) scenario
 * in which the user keeps on switching stream priorities around and
 * causing an infinite loop.
 */

#ifndef LSQUIC_SPI
#define LSQUIC_SPI 1

#include <stdint.h>


struct stream_prio_iter
{
    lsquic_cid_t                    spi_cid;            /* Used for logging */
    const char                     *spi_name;           /* Used for logging */
    uint64_t                        spi_set[4];         /* 256 bits */
    enum stream_flags               spi_onlist_mask;
    unsigned char                   spi_cur_prio;
    unsigned char                   spi_prev_prio;
    struct lsquic_stream           *spi_prev_stream,
                                   *spi_next_stream;
    struct lsquic_streams_tailq     spi_streams[256];
};


void
lsquic_spi_init (struct stream_prio_iter *, struct lsquic_stream *first,
         struct lsquic_stream *last, uintptr_t next_ptr_offset,
         unsigned onlist_mask, lsquic_cid_t cid, const char *name);

struct lsquic_stream *
lsquic_spi_first (struct stream_prio_iter *);

struct lsquic_stream *
lsquic_spi_next (struct stream_prio_iter *);

void
lsquic_spi_exhaust_on (struct stream_prio_iter *);

void
lsquic_spi_drop_non_high (struct stream_prio_iter *);

void
lsquic_spi_drop_high (struct stream_prio_iter *);

#endif
