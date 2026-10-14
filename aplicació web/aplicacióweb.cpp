#include <iostream>
#include <string>

class SessioUsuari {
private:
    std::string nomUsuari;
    int tempsLlimitSegons; // Invariant: Sempre ha de ser > 0
    bool activa;

    // Mètode privat d'ajuda. activa = false
    void tancarSessio() {
        activa = false;
    }

public:
    // Constructor per defecte: Usuari "convidat" amb límit de 300 segons
    SessioUsuari()
        : nomUsuari("convidat"), tempsLlimitSegons(300), activa(true) {
    }

    // Constructor parametritzat (1 paràmetre): Rep nomUsuari i assigna 600 s per defecte. De caràcter "explicit"
    explicit SessioUsuari(std::string nom)
        : nomUsuari(nom), tempsLlimitSegons(600), activa(true) {
    }

    // Constructor parametritzat complet: Rep nomUsuari i tempsLlimitSegons. Utilitza llista d'inicialització i valida l'invariant (si temps <= 0, assigna 60s per seguretat).
    SessioUsuari(std::string nom, int temps)
        : nomUsuari(nom), tempsLlimitSegons(temps > 0 ? temps : 60), activa(true) {
    }

    // Destructor (~SessioUsuari()): S'executa automàticament en sortir d'àmbit.
    ~SessioUsuari() {
        if (activa) {
            tancarSessio();
            std::cout << "[AUDITORIA] La sessio de '" << nomUsuari
                << "' s'ha tancat automaticament en sortir d'ambit.\n";
        }
    }

    // Mètodes d'encapsulació i negoci:

    // Retorna el nom de l'usuari (mètode const)
    std::string getNomUsuari() const {
        return nomUsuari;
    }

    // Retorna si la sessió està activa (mètode const)
    bool isActiva() const {
        return activa;
    }

    // Rebutja valors negatius o zero. Si és vàlid, suma els segons al límit actual.
    void ampliarTemps(int segons) {
        if (segons > 0) {
            tempsLlimitSegons += segons;
            std::cout << "S'han afegit " << segons << " segons a la sessio de "
                << nomUsuari << ". Nou limit: " << tempsLlimitSegons << "s.\n";
        }
        else {
            std::cout << "Error: Els segons a ampliar han de ser un valor estrictament positiu (> 0).\n";
        }
    }
};
//prova en el main
int main() {
    std::cout << "--- PROVA DE SESSIO PER DEFECTE ---\n";
    {
        SessioUsuari s1; // Convidat, 300s
        std::cout << "Usuari: " << s1.getNomUsuari() << "\n";
        std::cout << "Sessio activa? " << (s1.isActiva() ? "Si" : "No") << "\n";
    } // En sortir d'aquest bloc, es destruirà s1 i s'executarà el destructor [AUDITORIA]

    std::cout << "\n--- PROVA DE SESSIO AMB 1 PARMETRE (EXPLICIT) ---\n";
    {
        SessioUsuari s2("gerard");
        s2.ampliarTemps(120);
    } // En sortir d'aquest bloc, es destruirà s2

    std::cout << "\n--- PROVA DE SESSIO COMPLETA I VALIDACIO INVARIANT ---\n";
    {
        // Provem amb temps <= 0 per veure si s'assigna 60 segons per seguretat
        SessioUsuari s3("admin", -10);
        std::cout << "Usuari: " << s3.getNomUsuari() << "\n";
    } // En sortir d'aquest bloc, es destruirà s3

    return 0;
}