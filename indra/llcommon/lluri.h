/** 
 * @file lluri.h
 * @author Phoenix
 * @date 2006-02-05
 * @brief Declaration of the URI class.
 *
 * Copyright (c) 2006-$CurrentYear$, Linden Research, Inc.
 * $License$
 */

#ifndef LL_LLURI_H
#define LL_LLURI_H

#include <string>

class LLSD;
class LLUUID;
class LLApp;

/** 
 *
 * LLURI instances are immutable
 * See: http://www.ietf.org/rfc/rfc3986.txt
 *
 */
class LLURI
{
public:
  LLURI();
  LLURI(const std::string& escaped_str);
  LLURI(const std::string& scheme,
		const std::string& userName,
		const std::string& password,
		const std::string& hostName,
		U16 hostPort,
		const std::string& escapedPath,
		const std::string& escapedQuery);
	  
  // construct from escaped string, as would be transmitted on the net

	~LLURI();

	static LLURI buildHTTP(
		const std::string& prefix,
		const LLSD& path);

	static LLURI buildHTTP(
		const std::string& prefix,
		const LLSD& path,
		const LLSD& query);
	///< prefix is either a full URL prefix of the form
	/// "http://example.com:8080", or it can be simply a host and
	/// optional port like "example.com" or "example.com:8080", in
	/// these cases, the "http://" will be added

	static LLURI buildHTTP(
		const std::string& host,
		const U32& port,
		const LLSD& path);
	static LLURI buildHTTP(
		const std::string& host,
		const U32& port,
		const LLSD& path,
		const LLSD& query);

	std::string asString() const;
	///< the whole URI, escaped as needed
  
	/** @name Parts of a URI */
	//@{
	// These functions return parts of the decoded URI.  The returned
	// strings are un-escaped as needed
  
	// for all schemes
	std::string scheme() const;		///< ex.: "http", note lack of colon
	std::string opaque() const;		///< everything after the colon
  
  // for schemes that follow path like syntax (http, https, ftp)
  std::string authority() const;	// ex.: "host.com:80"
  std::string hostName() const;	// ex.: "host.com"
  std::string userName() const;
  std::string password() const;
  U16 hostPort() const;			// ex.: 80, will include implicit port
  BOOL defaultPort() const;		// true if port is default for scheme
  const std::string& escapedPath() const { return mEscapedPath; }
  std::string path() const;		// ex.: "/abc/def", includes leading slash
  //    LLSD pathArray() const;			// above decoded into an array of strings
  std::string query() const;		// ex.: "x=34", section after "?"
  const std::string& escapedQuery() const { return mEscapedQuery; }
  LLSD queryMap() const;			// above decoded into a map
  static LLSD queryMap(std::string escaped_query_string);

	/**
	 * @brief given a name value map, return a serialized query string.
	 *

	 * @param query_map a map of name value. every value must be
	 * representable as a string.
	 * @return Returns an url query string of '?n1=v1&n2=v2&...'
	 */
	static std::string mapToQueryString(const LLSD& query_map);

	/** @name Escaping Utilities */
	//@{
	// Escape a string by urlencoding all the characters that aren't
	// in the allowed string.
	static std::string escape(const std::string& str);
	static std::string escape(
		const std::string& str,
		const std::string & allowed); 
	static std::string unescape(const std::string& str);
	//@}

private:
	std::string mScheme;
	std::string mEscapedOpaque;
	std::string mEscapedAuthority;
	std::string mEscapedPath;
	std::string mEscapedQuery;
};

#endif // LL_LLURI_H
