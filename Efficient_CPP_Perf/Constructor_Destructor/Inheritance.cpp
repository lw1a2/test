class BaseLock
{
public:
	// (The LogSource object will be explained shortly)
	BaseLock(pthread_mutex_t &key, LogSource &lsrc) {};
	virtual ~BaseLock() {};
};

class MutexLock : public BaseLock
{
public:
	MutexLock (pthread_mutex_t &key, LogSource &lsrc);
	~MutexLock();
private:
	pthread_mutex_t &theKey;
	LogSource &src;
};

MutexLock::MutexLock(pthread_mutex_t& aKey, const LogSource& source)
: BaseLock(aKey, source),
theKey(aKey),
src(source)
{
	pthread_mutex_lock(&theKey);
#if defined(DEBUG)
	cout << "MutexLock " << &aKey << " created at " << src.file() <<
	"line" <<src.line() << endl;
#endif
}

MutexLock::~MutexLock()	// Destructor
{
	pthread_mutex_unlock(&theKey);

#if defined(DEBUG)
	cout << "MutexLock " << &aKey << " destroyed at " << src.file()<<
	"line" << src.line() << endl;
#endif
}

class BaseLogSource
{
public:
	BaseLogSource() {}
	virtual ~BaseLogSource() {}
};

class LogSource : public BaseLogSource
{
public:
	LogSource(const char *name, int num) : filename(name),
	lineNum(num) {}
	~LogSource() {}

	char *file();
	int line();
private:
	char *filename;
	int  lineNum;
};

int main()
{
	MutexLock myLock(theKey, LogSource(__FILE__, __LINE__));
	sharedCounter++;

	return 0;
}


