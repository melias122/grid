#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "app.h"

using namespace std;

class Vigenere {
public:

	string encrypt(const string &pt, const string &key) {
		string ct(pt.length(), 0);
		for (int i = 0; i < pt.length(); i++) {
			ct[i] = pt[i] - 'A';
			ct[i] = ((ct[i] + (key[i % key.length()] - 'A')) % 26) + 'A';
		}
		return ct;
	}

	string decrypt(const string &ct, const string &key) {
		string pt(ct.length(), 0);
		for (int i = 0; i < ct.length(); i++) {
			pt[i] = ct[i] - 'A';
			pt[i] = ((pt[i] - (key[i % key.length()] - 'A') + 26) % 26) + 'A';
		}
		return pt;
	}
};


class VigenereBreaker : public Bruteforcer {
public:
	VigenereBreaker(string ct, string pt, int maxKeyLength)
		: m_ct{ct},
		  m_pt{pt},
		  m_maxKeylen{maxKeyLength}
	{
		m_pt.resize(ct.size());
	}

	void run(int procId, int nproc) override {
		cout << procId << nproc << endl;
		if (procId > 26) {
			return;
		}

		cout << "VigenereBreaker " << procId << endl;
		string key(m_maxKeylen, 0);
		key[0] = procId + 'A';
		recursive(1, m_maxKeylen, key);
	}

private:
	void recursive(int level, int maxLevel, string &key)
	{
		if (level < maxLevel) {
			for (int i = 0; i < 26 && !done; i++) {
				key[level] = (char) (i + 'A');

				string guess = m_cipher.decrypt(m_ct, key);
				if (m_pt == guess) {
					cout << "Heslo je: " << key << endl;
					done = true;
				}

				recursive(level + 1, maxLevel, key);
				key[level] = 0;
			}
		}
	}

private:
	Vigenere m_cipher;
	int m_maxKeylen;
	string m_ct, m_pt;

	bool done{false};
};

static const string alphanum = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string randomString(const int len) {
	string s(len, 0);
	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % alphanum.length()];
	}
	return s;
}

int main(int argc, char *argv[]) {

	srand(time(NULL));

	int keySize, ptSize;
	try {
		ptSize = stoi(argv[1]);
		keySize = stoi(argv[2]);
	} catch (...) {
		cerr << argv[0] << " <plaintext size> <key size>\n";
		return EXIT_FAILURE;
	}

	string key = randomString(keySize);
	string pt = randomString(ptSize);

	Vigenere cipher;
	auto ct  = cipher.encrypt(pt, key);
	auto pt2 = cipher.decrypt(ct, key);
	if (pt != pt2) {
		cout << "test: encryption/decryption failed" << endl;
		return 1;
	}

	cout << key << endl;

	VigenereBreaker v(ct, pt, key.length());
	Runner::run(&v);

	return 0;
}
