#ifndef CR
#define CR
class Etre;
class ComportementRencontre
{
	public:
		ComportementRencontre(void);
		virtual ~ComportementRencontre(void);

		//virtual void operator() (Etre& e1,Etre& e2);
		virtual void operator() (Etre& e1,std::vector<Etre>& vecEtre) {};
	private:


};

#endif
