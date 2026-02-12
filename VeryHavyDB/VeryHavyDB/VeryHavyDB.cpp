
#include <map>
#include <iostream>
#include <string>
#include <memory>

using namespace std;
class VeryHeavyDatabase
{
public:
	virtual std::string get_data(const std::string& key) {
		return "Data:" + key;
	}

private:

};
class CachDB : public VeryHeavyDatabase
{
	unique_ptr<VeryHeavyDatabase> _realDB;
	map<string, string> _cache;

  public:
	CachDB(unique_ptr<VeryHeavyDatabase> _real_DB) : _realDB(move(_real_DB)) {}
	std::string get_data(const std::string& key) override {

		if (_cache.find(key) == _cache.end()) {
			cout << "Request to real DB" << endl;
			_cache[key] = _realDB->get_data(key);
		}
		else {
			cout << "Get from _cashe" << endl;
		}
		return _cache.at(key);
	}

};

class OneShotDB : public VeryHeavyDatabase {
private:
    VeryHeavyDatabase* _realDB;
    size_t _shots_left;
    size_t _max_shots;
    map<string, size_t> _access_count;

public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : _realDB(real_object), _max_shots(shots), _shots_left(shots) {
    }

    std::string get_data(const std::string& key) override {
        if (_shots_left == 0) {
            return "error";
        }

        // Проверяем, сколько раз уже запрашивали этот ключ
        if (_access_count.find(key) == _access_count.end()) {
            _access_count[key] = 0;
        }

        if (_access_count[key] < _max_shots) {
            _access_count[key]++;
            _shots_left--;
            return _realDB->get_data(key);
        }
        else {
            return "error";
        }
    }
};

int main()
{
	auto Cache = make_unique<CachDB>(move(make_unique<VeryHeavyDatabase>()));

	cout << Cache->get_data("Key1") << endl;
	cout << Cache->get_data("Key2") << endl;
	cout << Cache->get_data("Key1") << endl;
	cout << Cache->get_data("Key3") << endl;
	cout << Cache->get_data("Key3") << endl;

    cout << "\nOneShotDB:" << endl;
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(&real_db, 2);

    cout << limit_db.get_data("key") << endl;
    cout << limit_db.get_data("key") << endl;
    cout << limit_db.get_data("key") << endl;
    cout << limit_db.get_data("other_key") << endl;


	return 0;
}
