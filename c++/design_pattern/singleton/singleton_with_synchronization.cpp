#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic.hpp>

using namespace std;

struct Database{
	private : 
		static boost::atomic<Database*> instance;
		static boost::mutex mtx;

	public : 
		static Database& getInstance();
};
Database& Database::getInstance(){
	Database* db = instance.load(boost::memory_order_consume);
	if(!db){
		boost::mutex::scoped_lock lock(mtx);

		// 이 스레드가 mtx를 획득하는 동안 생성되지 않았는지 다시 확인
		Database* db = instance.load(boost::memory_order_consume);
		if(!db){
			db = new Database();
			instance.store(db, boost::memory_order_release);
		}

		db = new Database();
	}

	return *db;
}

int main(void){

	return 0;
}