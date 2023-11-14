#include <iostream>

using namespace std;

template<class T>
class LSLSE;

template<class T>
class SocioClub{
private:
    T NumeroSocio;
    T NombreSocio;
    T Domicilio;
    T AnoIngreso;
    SocioClub<T>* sig;
public:
    SocioClub():sig(nullptr){};
    friend class LSLSE<T>;
    
    friend ostream& operator<<(ostream& o, SocioClub<T>& s){
    	o<<endl;
        o<<"Numero de Socio: "<<s.NumeroSocio<<endl;
        o<<"Nombre de Socio: "<<s.NombreSocio<<endl;
        o<<"Domicilio: "<<s.Domicilio<<endl;
        o<<"Ano de Ingreso: "<<s.AnoIngreso<<endl;
        return o;
    }

    friend istream& operator>>(istream& i, SocioClub<T>& s){
        cout<<"Numero de Socio: ";
        i>>s.NumeroSocio;
        cout<<"Nombre de Socio: ";
        i>>s.NombreSocio;
        cout<<"Domicilio: ";
        i>>s.Domicilio;
        cout<<"Ano de Ingreso: ";
        i>>s.AnoIngreso;
        return i;
    }
    
    bool operator==(SocioClub<T>& o) const {
        return NumeroSocio == o.NumeroSocio && NombreSocio == o.NombreSocio && Domicilio == o.Domicilio && AnoIngreso == o.AnoIngreso;
    }
    
    SocioClub<T>& operator=(SocioClub<T>& o) {
        NumeroSocio = o.NumeroSocio;
        NombreSocio = o.NombreSocio;
        Domicilio = o.Domicilio;
        AnoIngreso = o.AnoIngreso;
    }
};

template<class T>
class LSLSE{
private:
    SocioClub<T>* lista;
public:
    LSLSE():lista(nullptr){};
    bool vacia()const;
    SocioClub<T>* ultimo()const;
    SocioClub<T>* primero()const;
    SocioClub<T>* anterior(SocioClub<T>* pos)const;
    void insertar(SocioClub<T>* pos,SocioClub<T> elem);
    bool eliminar(SocioClub<T>* pos);
    void imprimir()const;
    SocioClub<T>* localiza(SocioClub<T> elem) const;
    void registrarNuevoSocio();
    void darDeBajaSocio();
    SocioClub<T>* buscarPorNombre(const string& nombre) const;
    SocioClub<T>* buscarPorDomicilio(const string& domicilio) const;
    int calcularTotalSocios() const;
};

template<class T>
void LSLSE<T>::imprimir()const{
    SocioClub<T>* aux=lista;
    while(aux!=nullptr){
        std::cout<<*aux<<"-> ";
        aux=aux->sig;
    }
}

template<class T>
bool LSLSE<T>::eliminar(SocioClub<T>* pos){
    if(vacia() || pos==nullptr){
        return false;
    }
    if(pos==lista){
        lista=lista->sig;
    }
    else{
        anterior(pos)->sig=pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertar(SocioClub<T>* pos,SocioClub<T> elem){
    SocioClub<T>* aux = new SocioClub<T>(elem);
    if(pos==nullptr){
        aux->sig=lista;
        lista=aux;
    }
    else{
        aux->sig=pos->sig;
        pos->sig=aux;
    }
}

template<class T>
SocioClub<T>* LSLSE<T>::anterior(SocioClub<T>* pos)const{
    if(vacia() || pos==nullptr){
        return nullptr;
    }
    SocioClub<T>* aux=lista;
    while(aux!=nullptr && aux->sig!=pos){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
SocioClub<T>* LSLSE<T>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return lista;
}


template<class T>
SocioClub<T>* LSLSE<T>::ultimo()const{
    if(vacia()){
        return nullptr;
    }
    SocioClub<T>* aux=lista;
    while(aux->sig!=nullptr){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
SocioClub<T>* LSLSE<T>::localiza(SocioClub<T> elem)const{
    SocioClub<T>* aux = lista;
    if (vacia()){
        return nullptr;
    }

    while (aux != nullptr){
        if (*aux == elem){
            return aux;
        }
        aux = aux->sig;
    }
    return nullptr;
}

template<class T>
void LSLSE<T>::registrarNuevoSocio(){
    SocioClub<T> nuevoSocio;
    cin>>nuevoSocio;

    SocioClub<T>* pos = lista;
    SocioClub<T>* anteriorPos = nullptr;

    while (pos != nullptr && nuevoSocio.NumeroSocio > pos->NumeroSocio){
        anteriorPos = pos;
        pos = pos->sig;
    }
    insertar(anteriorPos, nuevoSocio);
}


template<class T>
bool LSLSE<T>::vacia()const{
    if(lista==nullptr)
        return true;
    return false;
}

template<class T>
int LSLSE<T>::calcularTotalSocios()const{
    int total = 0;
    SocioClub<T>* aux = lista;

    while(aux != nullptr){
        total++;
        aux = aux->sig;
    }
    return total;
}

template<class T>
void LSLSE<T>::darDeBajaSocio(){
    SocioClub<T> numSocioABaja;
    if(vacia()){
        cout << "La lista de socios esta vacia." << endl;
        return;
    }

    cout<<"Ingrese el socio a dar de baja: ";
    cin>>numSocioABaja;
    cout<<endl;
    SocioClub<T>* socioABaja = localiza(numSocioABaja);

    if(socioABaja != nullptr){
    	eliminar(socioABaja);
        cout<<"Socio dado de baja exitosamente."<<endl;
    }else{
        cout<<"No se encontrO un socio con ese nUmero."<<endl;
    }
}

template<class T>
SocioClub<T>* LSLSE<T>::buscarPorNombre(const string& nombre)const{
    SocioClub<T>* aux = lista;
    while(aux != nullptr){
        if(aux->NombreSocio == nombre){
            return aux;
        }
        aux = aux->sig;
    }
    return nullptr;
}

template<class T>
SocioClub<T>* LSLSE<T>::buscarPorDomicilio(const string& domicilio)const{
    SocioClub<T>* aux = lista;
    while(aux != nullptr){
        if(aux->Domicilio == domicilio){
            return aux;
        }
        aux = aux->sig;
    }
    return nullptr;
}

int main()
{
    LSLSE<string> milista;
    int opcion = 0;
    string nombre;
    string domicilio;
    SocioClub<string>* encontrado;
    
    while(opcion != 7){
    	cout<<endl;
    	cout<<"*****Menu de Socios*****"<<endl;
    	cout<<"1- Registrar Nuevo Socio"<<endl;
    	cout<<"2- Dar de Baja Socio"<<endl;
    	cout<<"3- Generar Reporte de Todos los Socios"<<endl;
    	cout<<"4- Buscar por Nombre Socio"<<endl;
    	cout<<"5- Buscar por Domicilio Socio"<<endl;
    	cout<<"6- Calcular el total de Socios registrados"<<endl;
    	cout<<"7- Salir"<<endl;
    	cout<<"Tu Opcion: ";
    	cin>>opcion;
    	switch(opcion){
    		case 1:
    			milista.registrarNuevoSocio();
    			break;
    		case 2:
    			milista.darDeBajaSocio();
    			break;
    		case 3:
    			milista.imprimir();
    			break;
    		case 4:
                cout<<"Ingrese el nombre a buscar: ";
                cin>>nombre;
                encontrado = milista.buscarPorNombre(nombre);
                if(encontrado != nullptr){
                    cout<<"Socio encontrado: "<<*encontrado<<endl;
                }else{
                    cout<<"No se encontrO un socio con ese nombre."<<endl;
                }
    			break;
    		case 5:
                cout<<"Ingrese el domicilio a buscar: ";
                cin>>domicilio;
                encontrado = milista.buscarPorDomicilio(domicilio);
                if(encontrado != nullptr){
                    cout<<"Socio encontrado: "<<*encontrado<<endl;
                }else{
                    cout<<"No se encontrO un socio con ese domicilio."<<endl;
                }
    			break;
    		case 6:
    			cout<<"Total de Socios registrados: "<<milista.calcularTotalSocios()<<endl;
    			break;
    		case 7:
    			cout<<"Saliendo...";
    			break;
    		default:
    			cout<<"Seleccione una opcion valida"<<endl;
		}
	}
    
    return 0;
}