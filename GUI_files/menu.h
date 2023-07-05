#ifndef MENU_H
#define MENU_H

#include "../blockchain_files/blockchain.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

/// Aspecto básico de todas las ventanas
class GUI : public nana::form{
private:
    nana::label title;
    nana::label header;
    nana::label foot;

public:
    BlockChain _blockchain;

    GUI() : nana::form(nana::API::make_center(800,600), appear::decorate<appear::taskbar>() ){
        this->caption(("Blockchain APP"));

        header.create(*this, nana::rectangle(0, 0, 800, 50));
        header.bgcolor(nana::colors::dark_blue);

        title.create(*this, nana::rectangle(200, 5, 400, 40));
        title.format(true);
        title.caption("<size = 25 red font=\"Consolas\"> BlockChain App");
        title.text_align(nana::align::center, nana::align_v::center);
        title.bgcolor(nana::colors::aquamarine);

        foot.create(*this, nana::rectangle(0, 550, 800, 50));
        foot.bgcolor(nana::colors::dark_blue);
    };

    void open(){
        this->show();
        nana::exec();
    }
};

void backToMenu(); /// Forward declarator

/// Ventana del menu de la blockchain
class bcMenu : public GUI {
private:
    nana::button see;
    nana::button add;
    nana::button modify;
    nana::button erase;
    nana::button recalculate;
    nana::button back;

public:
    bcMenu(){
        see.create(*this, nana::rectangle(325, 305, 150, 30));
        see.caption("Ver blockchain");

        add.create(*this, nana::rectangle(325,345, 150, 30));
        add.caption("Añadir transacción");

        modify.create(*this, nana::rectangle(325,385, 150, 30));
        modify.caption("Modificar bloque");

        erase.create(*this, nana::rectangle(325,425, 150, 30));
        erase.caption("Eliminar bloque");

        recalculate.create(*this, nana::rectangle(325,465, 150, 30));
        recalculate.caption("Recálculo en cascada");

        back.create(*this, nana::rectangle(325,505, 150, 30));
        back.caption("Volver al menú principal");
        back.events().click([&](){
            this->hide();
            backToMenu();
        });
    }
};

/// Ventana del menu de criterios de busqueda
class searchMenu : public GUI {
private:
    nana::button direct;
    nana::button range;
    nana::button prefix;
    nana::button pattern;
    nana::button max;
    nana::button min;
    nana::button back;

public:
    searchMenu(){
        direct.create(*this, nana::rectangle(325, 265, 150, 30));
        direct.caption("Búsqueda directa");

        range.create(*this, nana::rectangle(325,305, 150, 30));
        range.caption("Búsqueda por rango");

        prefix.create(*this, nana::rectangle(325,345, 150, 30));
        prefix.caption("Búsqueda por prefijo");

        pattern.create(*this, nana::rectangle(325,385, 150, 30));
        pattern.caption("Búsqueda por patrón");

        max.create(*this, nana::rectangle(325,425, 150, 30));
        max.caption("Máximo valor (de hash)");

        min.create(*this, nana::rectangle(325,465, 150, 30));
        min.caption("Mínimo valor (de hash)");

        back.create(*this, nana::rectangle(325,505, 150, 30));
        back.caption("Volver al menú principal");
        back.events().click([&](){
            this->hide();
            backToMenu();
        });
    }
};

/// Ventana del menu del calculos transaccionales
class calculationsMenu : public GUI {
private:
    nana::button moneyOfClient;
    nana::button moneyOfPlace;
    nana::button richestClient;
    nana::button richestLocation;
    nana::button back;

public:
    calculationsMenu(){
        moneyOfClient.create(*this, nana::rectangle(325, 305, 150, 30));
        moneyOfClient.caption("Dinero recaudado por cliente");

        moneyOfPlace.create(*this, nana::rectangle(325,345, 150, 30));
        moneyOfPlace.caption("Dinero movido en lugar");

        richestClient.create(*this, nana::rectangle(325,385, 150, 30));
        richestClient.caption("Cliente con más dinero recaudado");

        richestLocation.create(*this, nana::rectangle(325,425, 150, 30));
        richestLocation.caption("Lugar con más dinero movido");

        back.create(*this, nana::rectangle(325,465, 150, 30));
        back.caption("Volver al menú principal");
        back.events().click([&](){
            this->hide();
            backToMenu();
        });
    }
};

/// Ventana del menu principal
class mainMenu : public GUI {
private:
    nana::button blockchain;
    nana::button loadcsv;
    nana::button search;
    nana::button calculations;
    nana::button quit;

public:
    mainMenu(){
        blockchain.create(*this, nana::rectangle(325, 305, 150, 30));
        blockchain.caption("Mi Blockchain");
        blockchain.events().click([&](){
            this->hide();
            bcMenu().open();
        });

        loadcsv.create(*this, nana::rectangle(325,345, 150, 30));
        loadcsv.caption("Cargar CSV");
        loadcsv.events().click([this](){
            nana::inputbox::text path("Ruta del archivo");
            nana::inputbox filePath(*this,"Ingrese ruta del archivo .csv", "Cargar CSV");

            filePath.verify([&path](nana::window handle){
                if(path.value().empty()){
                    nana::msgbox mb(handle, "Ruta inválida");
                    mb << L"Ingrese una ruta válida.";
                    mb.show();
                    return false;
                }

                return true;
            });

            if(filePath.show_modal(path)){
                auto route = path.value();
                _blockchain.loadFromCSV(route);
            }
        });

        search.create(*this, nana::rectangle(325,385, 150, 30));
        search.caption("Criterios de búsqueda");
        search.events().click([&](){
            this->hide();
            searchMenu().open();
        });

        calculations.create(*this, nana::rectangle(325,425, 150, 30));
        calculations.caption("Cálculos Transaccionales");
        calculations.events().click([&](){
            this->hide();
            calculationsMenu().open();
        });

        quit.create(*this, nana::rectangle(325,465, 150, 30));
        quit.caption("Cerrar aplicación");
        quit.events().click(nana::API::exit);
    }
};

/// Hack para volver al menu
void backToMenu(){
    mainMenu().open();
}



#endif //MENU_H