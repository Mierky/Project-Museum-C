#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Obiecte_de_arta {
protected:
	string nume;
	int an;
	string artist;

public:
	Obiecte_de_arta() {
		this->nume = "NEINREGISTRAT";
		this->an = 0;
		this->artist = "NEINREGISTRAT";
	}

	Obiecte_de_arta(string nume, int an, string artist) {
		this->nume = nume;
		this->an = an;
		this->artist = artist;
	}

	Obiecte_de_arta(Obiecte_de_arta& o) {
		this->nume = o.nume;
		this->an = o.an;
		this->artist = o.artist;
	}

	string GetNume() {
		return this->nume;
	}
	void SetNume(string n) {
		this->nume = n;
	}

	int GetAn() {
		return this->an;
	}
	void SetAn(int a) {
		this->an = a;
	}

	string GetArtist() {
		return this->artist;
	}
	void SetArtist(string a) {
		this->artist = a;
	}

	virtual void Display(ostream& os) {
		os << "Denumire: " << this->nume << endl;
		os << "Anul realizarii: " << this->an << endl;
		os << "Numele artistului: " << this->artist << endl;
	}

	Obiecte_de_arta& operator=(Obiecte_de_arta& o) {
		this->nume = o.nume;
		this->an = o.an;
		this->artist = o.artist;
		return*this;
	}

	friend ostream& operator<<(ostream& os, Obiecte_de_arta* o) {
		o->Display(os);
		return os;
	}

	friend ostream& operator<<(ostream& os, Obiecte_de_arta& o) {
		o.Display(os);
		return os;
	}

	virtual void Read(istream& is) {
		cout << "Denumire: ";
		getline(is, this->nume);
		cout << "Anul realizarii: ";
		is >> this->an;
		is.ignore();
		cout << "Numele artistului: ";
		getline(is, this->artist);
	}

	friend istream& operator>>(istream& is, Obiecte_de_arta& o) {
		o.Read(is);
		return is;
	}

	friend istream& operator>>(istream& is, Obiecte_de_arta* o) {
		o->Read(is);
		return is;
	}

	virtual ~Obiecte_de_arta() {
		cout << "Destructor Obiecte_de_arta" << endl;
	}
};

class Picturi :public Obiecte_de_arta {
private:
	string tehnica;

public:
	Picturi() :Obiecte_de_arta() {
		this->tehnica = "NEINTRODUSA";
	}

	Picturi(string nume, int an, string artist, string tehnica) :Obiecte_de_arta(nume, an, artist) {
		this->tehnica = tehnica;
	}

	Picturi(Picturi& p) :Obiecte_de_arta(p) {
		this->tehnica = p.tehnica;
	}

	void Display(ostream& os) override {
		os << "--Pictura--" << endl;
		Obiecte_de_arta::Display(os);
		os << "Tehnica folosita: " << this->tehnica << endl;
	}

	string GetTehnica() {
		return this->tehnica;
	}
	void SetTehnica(string t) {
		this->tehnica = t;
	}

	Picturi& operator=(Picturi& p) {
		this->tehnica = p.tehnica;
		return *this;
	}

	friend ostream& operator<<(ostream& os, Picturi* p) {
		os << "Denumire: " << p->nume << endl;
		os << "Anul realizarii: " << p->an << endl;
		os << "Numele artistului: " << p->artist << endl;
		os << "Tehnica folosita: " << p->tehnica << endl;
		return os;
	}

	friend ostream& operator<<(ostream& os, Picturi& p) {
		os << "Denumire: " << p.nume << endl;
		os << "Anul realizarii: " << p.an << endl;
		os << "Numele artistului: " << p.artist << endl;
		os << "Tehnica folosita: " << p.tehnica << endl;
		return os;
	}

	void Read(istream& is) override {
		Obiecte_de_arta::Read(is);
		cout << "Tehnica folosita: ";
		is >> this->tehnica;
	}

	friend istream& operator>>(istream& is, Picturi& p) {
		cout << "Denumire: ";
		getline(is, p.nume);
		cout << "Anul realizarii: ";
		is >> p.an;
		is.ignore();
		cout << "Numele artistului: ";
		getline(is, p.artist);
		cout << "Tehnica utilizara: ";
		is >> p.tehnica;
		return is;
	}

	friend istream& operator>>(istream& is, Picturi* p) {
		cout << "Denumire: ";
		getline(is, p->nume);
		cout << "Anul realizarii: ";
		is >> p->an;
		is.ignore();
		cout << "Numele artistului: ";
		getline(is, p->artist);
		cout << "Tehnica utilizara: ";
		is >> p->tehnica;
		return is;
	}

	~Picturi() override {
		cout << "Destructor Picturi" << endl;
	}
};

class Sculpturi :public Obiecte_de_arta {
private:
	string material;

public:
	Sculpturi() :Obiecte_de_arta() {
		this->material = "NECUNOSCUT";
	}

	Sculpturi(string nume, int an, string artist, string material) :Obiecte_de_arta(nume, an, artist) {
		this->material = material;
	}

	Sculpturi(Sculpturi& s) :Obiecte_de_arta(s) {
		this->material = s.material;
	}

	string GetMaterial() {
		return this->material;
	}
	void SetMaterial(string m) {
		this->material = m;
	}

	void Display(ostream& os) override {
		os << "--Sculptura--" << endl;
		Obiecte_de_arta::Display(os);
		os << "Material folosit: " << this->material << endl;
	}

	void Read(istream& is) override {
		Obiecte_de_arta::Read(is);
		cout << "Material folosit: ";
		is >> this->material;
	}

	Sculpturi& operator=(Sculpturi& s) {
		this->material = s.material;
		return *this;
	}

	~Sculpturi() {
		cout << "Destructor Sculpturi" << endl;
	}
};

class Muzeu {
private:
	Obiecte_de_arta** colectie;
	int spatiu;

public:
	Muzeu() {
		this->spatiu = 0;
		this->colectie = new Obiecte_de_arta * [this->spatiu];
	}

	void operator+=(Obiecte_de_arta* obj) {
		Obiecte_de_arta** temp = new Obiecte_de_arta * [this->spatiu + 1];
		for (int i = 0; i < this->spatiu; i++) {
			temp[i] = this->colectie[i];
		}

		temp[this->spatiu] = obj;
		delete[]this->colectie;
		this->colectie = temp;
		this->spatiu++;
	}

	void operator-=(Obiecte_de_arta* obj) {
		int poz = -1;

		for (int i = 0; i < this->spatiu; i++) {
			if (this->colectie[i] == obj) {
				poz = i;
				break;
			}
		}

		if (poz != -1) {
			Obiecte_de_arta** temp = new Obiecte_de_arta * [this->spatiu - 1];

			for (int i = 0; i < poz; i++) {
				temp[i] = this->colectie[i];
			}

			for (int i = poz + 1; i < this->spatiu; i++) {
				temp[i - 1] = this->colectie[i];
			}

			delete[]this->colectie;
			this->colectie = temp;
			this->spatiu--;
		}
		else {
			throw out_of_range("Exceptie operator-=: Obiectul nu exista");
		}
	}

	Obiecte_de_arta* operator[](int poz) {
		if (poz >= this->spatiu || poz < 0) {
			throw out_of_range("Exceptie operator[]: Obiectul nu exista");
		}
		else return this->colectie[poz];
	}

	friend ostream& operator<<(ostream& os, Muzeu& obj) {
		os << "Spatiu destinat operelor de arta: " << obj.spatiu << endl;
		for (int i = 0; i < obj.spatiu; i++) {
			os << obj.colectie[i] << endl;
		}
		return os;
	}

	friend ofstream& operator<<(ofstream& ofs, Muzeu& obj) {
		ofs << obj.spatiu << endl; //Spatiu destinat operelor de arta
		for (int i = 0; i < obj.spatiu; i++) {
			ofs << obj.colectie[i] << endl;
		}
		return ofs;
	}
	/////////////////////////////////////EROARE1 - necesita implementarea ofstream in restul claselor 
	friend ifstream& operator>>(ifstream& ifs, Muzeu& obj) {
		int dim;
		ifs >> dim;

		delete[]obj.colectie;
		obj.colectie = new Obiecte_de_arta * [dim];

		for (int i = 0; i < dim; i++) {
			string identificator;
			ifs >> identificator;

			Obiecte_de_arta* o = nullptr;

			if (identificator == "--Pictura--") {
				o = new Picturi;
			}
			else if (identificator == "--Sculptura--") {
				o = new Sculpturi;
			}

			if (o != nullptr) {
				ifs >> o;
				obj += o;
			}
		}
		return ifs;
	}
	///////////////////////////////////////////////////////
	~Muzeu() {
		delete[]this->colectie;
		cout << "|~Muzeul s-a inchis~|" << endl;
	}
};

void main() {

	try {
		Obiecte_de_arta* o1 = new Picturi("Padurea Sfanta", 2000, "Iulian Iacob", "Acrilic");
		cout << o1 << endl;

		Obiecte_de_arta* o2 = new Picturi("Lacul", 2012, "Paul Ovidiu", "Ulei");
		cout << o2 << endl;

		Obiecte_de_arta* o3 = new Picturi(*dynamic_cast<Picturi*>(o2)); //copiere
		cout << o3 << endl;

		Obiecte_de_arta* o4 = new Sculpturi("Intruchiparea", 2023, "Constantin Brancus", "Lemn");
		cout << o4 << endl;

		o2->SetAn(3000);
		cout << o2 << endl << o3 << endl;

		Obiecte_de_arta* o6 = new Picturi;
		cin >> o6; cout << o6;

		cout << endl << "==================================" << endl;
		Muzeu muzeu;
		muzeu += o1; muzeu += o2; muzeu += o3; muzeu += o4; muzeu += o6;
		cout << muzeu;

		cout << "====================================FISIER:\n";

		ofstream ofs;
		ofs.open("Muzeu.txt", ios::out | ios::app);
		if (ofs.is_open()) {
			ofs << muzeu;
			ofs.close();
		}

		/*Muzeu m; //eroare1
		ifstream ifs;
		ifs.open("Muzeu.txt");
		ifs >> m;
		ifs.close();

		cout << m;*/

		ifstream ifs;
		ifs.open("Muzeu.txt", ios::in);
		if (ifs.is_open()) {
			string line;
			while (getline(ifs, line)) {
				cout << line << endl;
			}
			ifs.close();
		}

		delete o1; delete o2; delete o3; delete o6; delete o4;

	}
	catch (out_of_range ex) {
		cout << ex.what() << endl;
	}
}

/* MAI MULTE VERIFICARI IN MAIN:*/

	//Obiecte_de_arta a1("Pictura", 2020, "Pablo");
	//a1.Display();
	//a1.SetArtist("Ingi");
	//a1.Display();
	//Obiecte_de_arta a2("Pic", 2021, "Palo");
	//a1 = a2;
	//cout << a1;

	//cout << endl;

	//Picturi p1;
	//p1.Display();
	//Picturi p2("Peisajul", 2010, "Arian", "???");
	//p2.Display();
	//Picturi p3(p2);
	//p3.Display();
	//p1 = p3;
	//p1.Display();

	//cout << endl;
	//cout << p1;


	/*Obiecte_de_arta o4;
	cin >> o4; cout << o4; MERGE*/

	/*Picturi p;
	cin >> p; cout << p;*/ //MERGE

	/*Obiecte_de_arta* o5=new Obiecte_de_arta;
	cin >> o5; cout << o5;
	delete o5;	MERGE*/

	/*Picturi* p2 = new Picturi;
	cin >> p2; cout << p2;
	delete p2;*/ //MERGE

	/*Sculpturi s1;
	cout << s1;
	Sculpturi s2("Casuta", 1983, "Marcel", "otel");
	cout << s2;
	s1 = s2;
	cout << s1;
	Sculpturi s3(s2);
	cout << s3;*/ //MERG TOATE

	/*Sculpturi* s4 = new Sculpturi;
	cin >> s4; cout << s4; delete s4;*/ //MERGE

	/*Obiecte_de_arta* o7 = new Sculpturi;
	cin >> o7; cout << o7; delete o7;*/ //MERGE
