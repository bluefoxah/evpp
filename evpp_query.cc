/*
 * evpp_query.cc
 * Copyright (C) 2011 Thomas R. Dial <evpp@kavaga.com>
 * All Rights Reserved
 */
#include <string.h>
#include "evpp_query.h"

namespace {
  std::string theEmptyString("");
} // end: anonymous namespace

namespace evpp {

Query::Query(struct evhttp_request* request) :
  m_uri(NULL),
  m_parsed(false)
{
  memset(&m_headers, 0, sizeof(m_headers));
  if (!request) {
    return;
  }
  
  const char* encodedUri = evhttp_request_get_uri(request);  
  if (!encodedUri) {
    return;
  }
  
  m_uri = evhttp_uri_parse(encodedUri);
  if (!m_uri) {
    return;
  }
  
  const char* query = evhttp_uri_get_query(m_uri);
  if (!query) {
    return;
  }
  
  int status = evhttp_parse_query_str(query, &m_headers);
  m_parsed = (0 == status);
}  

Query::~Query()
{
  if (m_parsed) {
    evhttp_clear_headers(&m_headers);
  }
  if (m_uri) {
    evhttp_uri_free(m_uri);
    m_uri = NULL;
  }
}

std::string Query::operator[](const char* name) const
{
  if (name) {
    const char* value = find(name);
    if (value) {
      return std::string(value);
    }
  }
  return theEmptyString;
}

std::string Query::operator[](const std::string& name) const
{
  return (*this)[name.c_str()]; 
}

const char* Query::find(const char* param) const
{
  if (m_parsed && (NULL != param)) {
    return evhttp_find_header(&m_headers, param);
  }
  return NULL;
}

bool Query::was_parsed() const 
{
  return m_parsed;
}

} // end: namespace evpp
