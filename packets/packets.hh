#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>

#include "con_req.hh"
#include "con_resp.hh"
#include "constat_req.hh"
#include "constat_resp.hh"
#include "disc_req.hh"
#include "disc_resp.hh"
#include "tun_req.hh"
#include "tun_resp.hh"

static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);

static_assert(sizeof(boost::endian::big_uint8_t) == 1);
static_assert(sizeof(boost::endian::big_uint16_t) == 2);
static_assert(sizeof(boost::endian::big_uint32_t) == 4);
