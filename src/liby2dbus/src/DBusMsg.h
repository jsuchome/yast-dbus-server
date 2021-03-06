/*
  DBusMsg
*/

#ifndef DBUSMSG_H
#define DBUSMSG_H

#include <string>
#include <dbus/dbus.h>

#include <ycp/TypePtr.h>

class YCPValue;
class YCPList;
class YCPMap;

// DBusMessage wrapper
class DBusMsg
{

    public:

	DBusMsg();
	~DBusMsg();

	// copying functions
	DBusMsg(const DBusMsg &);
	DBusMsg &operator = (const DBusMsg &);

	// create a method call
	void createCall(const std::string &service, const std::string &object,
	    const std::string &interface, const std::string &method);

	// create a reply
	void createReply(const DBusMsg &m);

	// create an error (exception)
	void createError(const DBusMsg &m, const std::string &error_msg,
	    // use the generic code by default
	    const std::string &error_code = std::string(DBUS_ERROR_FAILED));

	bool addString(const std::string &val);
	bool addInt64(dbus_int64_t val);
	bool addInt32(dbus_int32_t val);
	bool addBoolean(dbus_bool_t val);
	bool addDouble(double val);

	bool addYCPValue(const YCPValue &val);
	bool addValueAs(const YCPValue &val, constTypePtr rettype = NULL);

	// ycptype may be Type::Any
	YCPValue getYCPValue(int index, constTypePtr ycptype) const;

	bool isMethodCall(const std::string &interface, const std::string &method) const;
	int arguments() const;
	int type() const;
	bool empty() const;

	DBusMessage *getMessage() const;
	void setMessage(DBusMessage *message);

	std::string interface() const;
	std::string method() const;
	std::string path() const;
	std::string sender() const;

	static const char *YCPValueSignature();
	static std::string YCPTypeSignature(constTypePtr type);

    private:

	bool addValue(int type, void* data);
	bool addValue(int type, void* data, DBusMessageIter *i);
	bool addValueAt(const YCPValue &val, DBusMessageIter *i, constTypePtr rtype = NULL);
	bool addYCPValue(const YCPValue &v, DBusMessageIter *i);
	bool addYCPValueRaw(const YCPValue &val, DBusMessageIter *i);
	void release();
	DBusMessage *msg;

	int typeInt(const YCPValue &val) const;
	std::string typeStr(const YCPValue &val, bool bsv_enc = true) const;

	YCPValue getYCPValue(DBusMessageIter *it, constTypePtr ycptype) const;
	YCPValue getYCPValueRawType(DBusMessageIter *it, constTypePtr ycptype) const;
	YCPValue getYCPValueRawAny(DBusMessageIter *it) const;
	YCPValue getYCPValueBsv(DBusMessageIter *it, constTypePtr ycptype) const;

	const char * getString(DBusMessageIter *it) const;
	YCPList getYCPValueList(DBusMessageIter *it, constTypePtr valuetype) const;
	YCPMap getYCPValueMap(DBusMessageIter *it, constTypePtr keytype, constTypePtr valuetype) const;
	YCPValue getYCPValueInteger(DBusMessageIter *it) const;

};

class DBusException
{
    std::string m_name;
    std::string m_message;
public:
    DBusException(const std::string& name, const std::string& message)
	:m_name(name), m_message(message) {}
    std::string name() const { return m_name; }
    std::string message() const { return m_message; }
};

class SignatureException : std::exception
{
    public:
	SignatureException();
};

#endif
