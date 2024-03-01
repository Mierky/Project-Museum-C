#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

enum class TipMancare {
	Nimic,Vegan,Vegetarian,Raw
};

ostream& operator<<(ostream& os, const TipMancare& tm) {
	switch (tm) {
	case TipMancare::Nimic:os << "Nimic"; break;
	case TipMancare::Vegan:os << "Vegan"; break;
	case TipMancare::Vegetarian:os << "Vegetarian"; break;
	case TipMancare::Raw:os << "Raw"; break;
	}
	return os;
}

istream& operator>>(istream& is, TipMancare& tm) {
	string input;
	is >> input;

	if (input == "Nimic") {
		tm = TipMancare::Nimic;
	}
	else if (input == "Vegan") {
		tm = TipMancare::Vegan;
	}
	else if (input == "Vegetarian") {
		tm = TipMancare::Vegetarian;
	}
	else if (input == "Raw") {
		tm = TipMancare::Raw;
	}
	else {
		tm = TipMancare::Nimic;
	}

	return is;
}


class Preparate {
protected:
	char* denumireMancare;
	float pret;
	TipMancare tm;
	int nrIngrediente;
	string* denumireIngrediente;
	float* cantitateIngrediente;
	const int nrMancare;
	static int counter;
public:
	//CONSTRUCTORI ///////////////////////////////////////////////////////////////
	Preparate():nrMancare(counter++) {
		this->denumireMancare = new char[strlen("Neidentificat") + 1];
		strcpy_s(this->denumireMancare, strlen("Neidentificat") + 1, "Neidentificat");
		this->pret = 0.0;
		this->tm = TipMancare::Nimic;
		this->nrIngrediente = 0;
		this->denumireIngrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->denumireIngrediente[i] = "nimic";
		}
		this->cantitateIngrediente = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitateIngrediente[i] = 0.0;
		}

	}
	
	Preparate(const char* denumire, float pret, TipMancare tm, int nrIngrediente, string* denumireIngrediente, float* cantitateIngrediente) :nrMancare(counter++) {
		this->denumireMancare = new char[strlen(denumire) + 1];
		strcpy_s(this->denumireMancare, strlen(denumire) + 1, denumire);
		this->pret = pret;
		this->tm = tm;
		this->nrIngrediente = nrIngrediente;
		this->denumireIngrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->denumireIngrediente[i] = denumireIngrediente[i];
		}
		this->cantitateIngrediente = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitateIngrediente[i] = cantitateIngrediente[i];
		}
	}

	Preparate(const Preparate& p):nrMancare(p.nrMancare) {
		this->denumireMancare = new char[strlen(p.denumireMancare) + 1];
		strcpy_s(this->denumireMancare, strlen(p.denumireMancare) + 1, p.denumireMancare);
		this->pret = p.pret;
		this->tm = p.tm;
		this->nrIngrediente = p.nrIngrediente;
		this->denumireIngrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->denumireIngrediente[i] = p.denumireIngrediente[i];
		}
		this->cantitateIngrediente = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitateIngrediente[i] = p.cantitateIngrediente[i];
		}
	}
	Preparate(const Preparate* p) :nrMancare(p->nrMancare) {
		this->denumireMancare = new char[strlen(p->denumireMancare) + 1];
		strcpy_s(this->denumireMancare, strlen(p->denumireMancare) + 1, p->denumireMancare);
		this->pret = p->pret;
		this->tm = p->tm;
		this->nrIngrediente = p->nrIngrediente;
		this->denumireIngrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->denumireIngrediente[i] = p->denumireIngrediente[i];
		}
		this->cantitateIngrediente = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitateIngrediente[i] = p->cantitateIngrediente[i];
		}
	}
	
	//GETTERS/SETTERS ///////////////////////////////////////////////////////////////
	char* getDenumireMancare(){
		return this->denumireMancare;
	}
	void setDenumireMancare(const char*den) {
		delete[]this->denumireMancare;
		this->denumireMancare = new char[strlen(den) + 1];
		strcpy_s(this->denumireMancare, strlen(den) + 1, den);
		
	}

	float getPret() {
		return this->pret;
	}
	void setPret(float v) {
		this->pret = v;
	}

	TipMancare getTipMancare() {
		return this->tm;
	}
	void setTipMancare(TipMancare t) {
		this->tm = t;
	}

	int getNrIngrediente() {
		return this->nrIngrediente;
	}

	float* getCantitateIngrediente() {
		return this->cantitateIngrediente;
	}

	string* getDenumireIngrediente() {
		return this->denumireIngrediente;
	}

	void setDenumireCantitate(int nr, string* den, float* cant) {
		this->nrIngrediente = nr;
		
		delete[]this->denumireIngrediente;
		delete[]this->cantitateIngrediente;
		this->denumireIngrediente = new string[this->nrIngrediente];
		this->cantitateIngrediente = new float[this->nrIngrediente];

		for (int i = 0; i < this->nrIngrediente; i++) {
			this->denumireIngrediente[i] = den[i];
		}
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitateIngrediente[i] = cant[i];
		}

	}

	int getNrMancare() {
		return this->nrMancare;
	}
	//OPERATOR << | >> ////////////////////////////////////////////////////////////////////////
	virtual void Display(ostream& os) const{
		os << "NrMancare: " << this->nrMancare << endl;
		os << "Denumire: " << this->denumireMancare << endl;
		os << "Pret: " << this->pret << " lei" << endl;
		os << "TipMancare: " << this->tm << endl;
		os << "Nr.Ingrediente: " << this->nrIngrediente << endl;
		os << "Denumire Ingrediente: ";
		for (int i = 0; i < this->nrIngrediente; i++) {
			os << this->denumireIngrediente[i] << ", ";
		}
		os << endl;
		os << "Cantitate Ingrediente: ";
		for (int i = 0; i < this->nrIngrediente; i++) {
			os << this->cantitateIngrediente[i] << " grame, ";
		}
		os << endl;
	}

	virtual void Read(istream& is) {
		cout << "Introduceti denumirea: ";
		char aux[100];
		is.getline(aux, 100);
		delete[]this->denumireMancare;
		this->denumireMancare = new char[strlen(aux) + 1];
		strcpy_s(this->denumireMancare, strlen(aux) + 1, aux);

		cout << "Introduceti pretul: ";
		is >> this->pret;
		cout << "Introduceti tipul de mancare: ";
		is >> this->tm;
		cout << "Introduceti numarul de ingrediente: ";
		is >> this->nrIngrediente;
		cout << "Introduceti denumirea ingredientelor: ";
		delete[]this->denumireIngrediente;
		this->denumireIngrediente = new string[this->nrIngrediente];
		is.ignore();
		for (int i = 0; i < this->nrIngrediente; i++) {
			getline(is,this->denumireIngrediente[i]);
		}
		cout << "Introduceti cantitatea ingredientelor: ";
		delete[]this->cantitateIngrediente;
		this->cantitateIngrediente = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			is >> this->cantitateIngrediente[i];
		}
	}

	friend istream& operator>>(istream& is, Preparate& p) {
		p.Read(is);
		return is;
	}
	friend istream& operator>>(istream& is, Preparate* p) {
		p->Read(is);
		return is;
	}

	friend ostream& operator<<(ostream& os, const Preparate& p) {
		p.Display(os);
		return os;
	}
	friend ostream& operator<<(ostream& os, const Preparate* p) {
		p->Display(os);
		return os;
	}
	//OPERATOR = ////////////////////////////////////////////////////////////////////////
	Preparate& operator=(const Preparate& p) {
		if (this != &p) {
			delete[]this->denumireMancare;
			delete[]this->denumireIngrediente;
			delete[]this->cantitateIngrediente;

			this->denumireMancare = new char[strlen(p.denumireMancare) + 1];
			strcpy_s(this->denumireMancare, strlen(p.denumireMancare) + 1, p.denumireMancare);
			this->pret = p.pret;
			this->tm = p.tm;
			this->nrIngrediente = p.nrIngrediente;
			this->denumireIngrediente = new string[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				this->denumireIngrediente[i] = p.denumireIngrediente[i];
			}
			this->cantitateIngrediente = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				this->cantitateIngrediente[i] = p.cantitateIngrediente[i];
			}
		}
		return* this;
	}
	//OPERATOR ++(),++,== ///////////////////////////////////////////////////////////////
	void operator++() {
		this->pret++;
	}
	Preparate operator++(int){
		Preparate copie=*this;
		++(this->pret);
		return copie;
	}
	string operator==(const Preparate& p) {
		if (this->pret == p.pret) {
			return "Preturile sunt identice";
		}
		else return "Preturile difera";
	}

	//OFSTREAM | IFSTREAM //////////////////////////////////////////FISIERE/////////////////////

	virtual void DisplayTXT(ofstream& ofs) {
		ofs << this->denumireMancare << endl;
		ofs << this->pret << endl;
		ofs << this->tm << endl;
		ofs << this->nrIngrediente << endl;
		for (int i = 0; i < this->nrIngrediente; i++) {
			ofs << this->denumireIngrediente[i] << endl;
		}
		for (int i = 0; i < this->nrIngrediente; i++) {
			ofs << this->cantitateIngrediente[i] << endl;
		}
	}

	friend ofstream& operator<<(ofstream& ofs, Preparate& p) {
		p.DisplayTXT(ofs);
		cout << "S-A ADAUGAT IN FISIER" << endl;
		return ofs;
	}
	friend ofstream& operator<<(ofstream& ofs, Preparate* p) {
		p->DisplayTXT(ofs);
		cout << "S-A ADAUGAT IN FISIER" << endl;
		return ofs;
	}


	virtual void ReadTXT(ifstream& ifs) {
		char aux[100];
		ifs.getline(aux, 100);
		delete[]this->denumireMancare;
		this->denumireMancare = new char[strlen(aux) + 1];
		strcpy_s(this->denumireMancare, strlen(aux) + 1, aux);

		ifs >> this->pret;
		ifs >> this->tm;
		ifs >> this->nrIngrediente;

		delete[]this->denumireIngrediente;
		this->denumireIngrediente = new string[this->nrIngrediente];
		ifs.ignore();
		for (int i = 0; i < this->nrIngrediente; i++) {
			getline(ifs, this->denumireIngrediente[i]);
		}
		delete[]this->cantitateIngrediente;
		this->cantitateIngrediente = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			ifs >> this->cantitateIngrediente[i];
		}
	}
	friend ifstream& operator>>(ifstream& ifs, Preparate& p) {
		p.ReadTXT(ifs);
		return ifs;
	}
	friend ifstream& operator>>(ifstream& ifs, Preparate* p) {
		p->ReadTXT(ifs);
		return ifs;
	}


	//DESTRUCTOR ///////////////////////////////////////////////////////////////
	~Preparate() {
		delete[]this->denumireIngrediente;
		delete[]this->denumireMancare;
		delete[]this->cantitateIngrediente;
	}
};

class PreparatePentruCopii :public Preparate {
private:
	string jucarie;
public:
	//CONSTRUCTORI ///////////////////////////////////////////////////////////////
	PreparatePentruCopii():Preparate() {
		this->jucarie = "Nimic";
	}
	PreparatePentruCopii(const char* denumire, float pret, TipMancare tm, int nrIngrediente, string* denumireIngrediente, float* cantitateIngrediente,string jucarie) :Preparate(denumire, pret, tm, nrIngrediente, denumireIngrediente, cantitateIngrediente) {
		this->jucarie = jucarie;
	}
	PreparatePentruCopii(const PreparatePentruCopii& p):Preparate(p) {
		this->jucarie = p.jucarie;
	}

	//GETTERS/SETTERS//////////////////////////////////////////////////

	string getJucarie() {
		return this->jucarie;
	}
	void setJucarie(string v) {
		this->jucarie = v;
	}
	//OPERATOR == ////////////////////////////////////////////////////////////////////////

	PreparatePentruCopii& operator=(const PreparatePentruCopii& p) {
		Preparate::operator=(p);
		this->jucarie = p.jucarie;
		return* this;
	}

	//OPERATOR << | >> ////////////////////////////////////////////////////////////////////////

	void Display(ostream& os) const {
		Preparate::Display(os);
		os << "Jucarie: " << this->jucarie << endl;
	}

	void Read(istream& is) {
		Preparate::Read(is);
		cout << "Introduceti jucaria: ";
		getline(is, this->jucarie);
	}

	void DisplayTXT(ofstream& ofs) {
		Preparate::DisplayTXT(ofs);
		ofs << this->jucarie << endl;
	}

	void ReadTXT(ifstream& ifs) {
		Preparate::ReadTXT(ifs);
		ifs.ignore();
		getline(ifs, this->jucarie);
	}

	//DOWNCASTING ////////////////////////////////////////////////////////////////////////
	PreparatePentruCopii(Preparate& p) :Preparate(p) {
		this->jucarie = "O jucarie frumoasa";
	}

	~PreparatePentruCopii(){}
	
};

class Meniu {
private:
	int dimensiune;
	Preparate** vector;
public:
	Meniu() {
		this->dimensiune = 0;
		this->vector = new Preparate * [0];
	}

	void operator+=(Preparate*p) {
		Preparate** aux = new Preparate * [this->dimensiune + 1];
		for (int i = 0; i < this->dimensiune; i++) {
			aux[i] = this->vector[i];
		}
		aux[this->dimensiune] = p;
		delete[]this->vector;
		this->vector = aux;
		this->dimensiune++;
	}

	void operator-=(Preparate* p) {
		int poz=-1;
		for (int i = 0; i < this->dimensiune; i++) {
			if (this->vector[i] == p) {
				poz = i;
				break;
			}
		}

		if (poz != -1) {
			Preparate** aux = new Preparate * [this->dimensiune - 1];

			for (int i = 0; i < poz; i++) {
				aux[i] = this->vector[i];
			}
			for (int i = poz + 1; i < this->dimensiune; i++) {
				aux[i - 1] = this->vector[i];
			}
			delete[]this->vector;
			this->vector = aux;
			this->dimensiune--;
		}
		else {
			throw out_of_range("Exceptie operator -=: Obiectul nu exista");
		}
	}

	Preparate* operator[](int index) {
		if (index > this->dimensiune || index < 0) {
			throw out_of_range("Exceptie operator []: Obiectul nu exista");
		}
		else return this->vector[index];
	}

	friend ostream& operator<<(ostream& os, Meniu& m) {
		os << "Numar de preparate: " << m.dimensiune<<endl<<endl;
		for (int i = 0; i < m.dimensiune; i++) {
			os << m.vector[i]<<endl;
		}
		return os;
	}

	~Meniu() {
		delete[]this->vector;
	}
};

int Preparate::counter = 1;

void main() {
	Preparate p1;
	cout << p1<<endl;
	Preparate p2("Salata", 30, TipMancare::Vegan, 2, new string[2]{ "Rosii","Castraveti" }, new float[2] {30, 40});
	cout << p2<<endl;
	Preparate p3;
	p3.setDenumireMancare("Piure");
	p3.setPret(20);
	p3.setTipMancare(TipMancare::Vegan);
	p3.setDenumireCantitate(2, new string[2]{ "Cartofi","Sare" }, new float[2] {100, 10});
	
	/*cout << p3.getNrMancare() << endl << p3.getDenumireMancare() << endl << p3.getPret() << endl << p3.getTipMancare() << endl <<p3.getNrIngrediente()<<endl;
	for (int i = 0; i < p3.getNrIngrediente(); i++) {
		cout << p3.getDenumireIngrediente()[i]<<", ";
	}
	cout << endl;
	for (int i = 0; i < p3.getNrIngrediente(); i++) {
		cout << p3.getCantitateIngrediente()[i]<<" grame, ";
	}
	cout << endl<<endl;*/
	
	//Preparate p4(p3); cout << p4 << endl;

	Preparate* p5 = new Preparate(p3);
	cout << p5 << endl;

	Preparate* p6 = new Preparate(p5); cout << p6 << endl;
	
	Preparate* p7 = new Preparate;
	*p7 = *p6; /*cout << p7 << endl;*/ //!!!!trebuie * la ambele
	//Preparate p6; cin >> p6; cout <<endl<< p6 << endl;

	++(*p7);
	cout << p7 << endl;

	/*cout << (*p7)++ << endl; cout << p7<<endl;*/ 
	//cout << (*p7 == p1)<<endl; 

	//FISIERE////////////////////////
	//ofstream ofs;
	//ofs.open("Preparate.txt", ios::out|ios::trunc);
	//ofs << p5;
	//ofs.close();

	//Preparate txt;
	//ifstream ifs;
	//ifs.open("Preparate.txt", ios::in);
	//cout << "---------------TXT SE CITESTE-------------------" << endl;
	//if (ifs.is_open()) {
	//	ifs >> txt;
	//	cout << txt << endl;
	//	cout << "TXT A FOST CITIT" << endl;
	//	ifs.close();
	//}
	//else cout << "Fisierul nu a fost gasit"<<endl;
	cout << "------------------------------AFISARE CLASA DERIVATA-------------------------------------------" << endl;
	PreparatePentruCopii pc;
	PreparatePentruCopii pc1("Salata", 30, TipMancare::Vegan, 2, new string[2]{ "Rosii","Castraveti" }, new float[2] {30, 40}, "Masina");
	PreparatePentruCopii pc2(pc1);

	cout << pc << endl << pc1 << endl << pc2 << endl;

	//PreparatePentruCopii istream;
	//cin >> istream; cout << istream;
	PreparatePentruCopii* pcp = new PreparatePentruCopii(pc1);
	PreparatePentruCopii* pcp1 = new PreparatePentruCopii;
	*pcp1 = *pcp; 
	cout << pcp<<endl;
	cout << pcp1<<endl;
	delete pcp; delete pcp1;

	cout << "--------------UPCASTING SI DOWNCASTING--------------" << endl;

	PreparatePentruCopii down(*p7);
	Preparate up(pc1);
	cout << down << endl << up << endl;

	//FISIERE - DERIVATE:
	/*ofstream ofs("PreparatePentruCopii.txt", ios::out);
	ofs << pc2;
	cout << "PreparatePentruCopii.txt a fost realizat" << endl;
	ofs.close();

	cout <<endl<< "-----------------------AFISARE TXT-----------------------" << endl;
	PreparatePentruCopii txt_copii;
	ifstream ifs("PreparatePentruCopii.txt", ios::in);
	if (ifs.is_open()) {
		ifs >> txt_copii;
		cout << txt_copii<<endl;
	}
	else cout << "Nu a fost gasit fisierul";*/

	cout << "-------------------Lucru cu VECTOR-------------------------------";

	try {
		Preparate* pv = new PreparatePentruCopii;
		Preparate* pv1 = new PreparatePentruCopii(pc1);

		Meniu m;
		m += pv; m += pv1; m += p5; m += p7;
		cout <<endl<< m << endl;
		/*cout << endl;
		cout << m[2] << endl<<endl;
		m -= pv1;
		cout << m << endl;*/

	}
	catch (out_of_range ex) {
		cout << ex.what() << endl;
	}


	delete p5; delete p6; delete p7;
}