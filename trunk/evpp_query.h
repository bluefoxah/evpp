/*
 * evpp_query.h
 * Copyright (C) 2011 Thomas R. Dial <evpp@kavaga.com>
 * All Rights Reserved  
 *
 * Helper class that makes it easier to parse query parameters that are
 * encoded in a libevent request.  This class makes no assumptions about the
 * inputs.  You can pass a NULL request object, NULL strings to the find()
 * function, etc,.  However, find() will return NULL if nothing has been 
 * found, and the operator functions will return the empty string.  If you 
 * really need to find out if a set of arguments was actually parsed, you
 * may call the was_parsed() function.  This indicates that the request was
 * valid, the query string existed, and was parsed into a set of 'headers.'
 */
#ifndef EVPP_QUERY_H
#define EVPP_QUERY_H

#include <event2/http.h>
#include <event2/keyvalq_struct.h>
#include <string>

namespace evpp {

class Query
{
public:
  Query(struct evhttp_request* request);
  ~Query();
  
  // Indexers return the empty string if the query parameter is not found.
  std::string operator[](const char* name) const;
  std::string operator[](const std::string& name) const;  

  // find() accepts NULL, but also *returns* NULL if no value is found.
  const char* find(const char* param) const;
  
  // Returns true if a query was parsed.
  bool was_parsed() const;

private:
  evhttp_uri*       m_uri;
  struct evkeyvalq  m_headers;
  bool              m_parsed;

  Query(const Query&);
  Query& operator=(const Query&);      
};

} // end: namespace evpp

#endif
