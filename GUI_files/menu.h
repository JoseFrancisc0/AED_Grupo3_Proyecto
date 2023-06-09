#ifndef MENU_H
#define MENU_H

#include "../blockchain_files/blockchain.h"
#include <filesystem>
#include <string>
#include <vector>
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/picture.hpp>

/// Aspecto básico de todas las ventanas
class GUI : public nana::form{
private:
    nana::label title;
    nana::label header;
    nana::label foot;
    nana::picture pic;

protected:
    BlockChain& _blockchain;

public:
    GUI(BlockChain& bc) : nana::form(nana::API::make_center(800,600), appear::decorate<appear::taskbar>()), _blockchain(bc){
        this->caption(("Blockchain App"));

        header.create(*this, nana::rectangle(0, 0, 800, 50));
        header.bgcolor(nana::colors::dark_blue);

        title.create(*this, nana::rectangle(200, 5, 400, 40));
        title.format(true);
        title.caption("<size = 25 red font=\"Consolas\"> BlockChain App");
        title.text_align(nana::align::center, nana::align_v::center);
        title.bgcolor(nana::colors::aquamarine);

        pic.create(*this);
        /// Encontrar la imagen
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::string buildDir = "cmake-build-debug"; /// For Clion
        std::size_t pos = currentPath.string().find(buildDir);
        std::string projectDir = currentPath.string().substr(0, pos);

        pic.load( nana::paint::image(projectDir+"\\GUI_files\\image.bmp"));

        nana::rectangle picRect(175, 55, 500, 200);
        pic.move(picRect);

        foot.create(*this, nana::rectangle(0, 550, 800, 50));
        foot.bgcolor(nana::colors::dark_blue);
    };

    void open(){
        this->show();
        nana::exec();
    }
};

void backToMenu(BlockChain& bc); /// Forward declarator

/// Ventana del menu de la blockchain
class bcMenu : public GUI {
private:
    nana::button see;
    nana::button add;
    nana::button modify;
    nana::button erase;
    nana::button recalculate;
    nana::button back;
    /// Para ver la blockchain
    nana::form* bcListWin;
    nana::listbox bcListLb;
    nana::button bcListClose;
public:
    bcMenu(BlockChain& _bc) : GUI(_bc){
        see.create(*this, nana::rectangle(325, 305, 150, 30));
        see.caption("Ver blockchain");
        see.events().click([this](){
            bcListWin = new nana::form(nana::API::make_center(600,440));
            bcListWin->caption("BlockChain List");

            bcListLb.create(*bcListWin, nana::rectangle(0,0,600,400));

            /// Headers de la lista
            bcListLb.append_header("i", 20);
            bcListLb.append_header("BlockHash");
            bcListLb.append_header("PreviousHash");
            bcListLb.append_header("Client");
            bcListLb.append_header("Location");
            bcListLb.append_header("Amount");
            bcListLb.append_header("Date");

            /// Get all blocks for GUI
            std::vector<Block> blocks = _blockchain.constructGUIBlockVector();

            /// Imprimir en la consola para copiar hashes
            for(auto block : blocks){
                block.printBlock();
                std::cout << '\n';
            }
            std::cout << "===========================================================" << '\n';

            for(int i=0; i<blocks.size(); i++){
                auto _time = blocks[i].getTransaction().getDate();
                /// Para el tiempo
                char buffer[80];
                struct tm* timeinfo;
                timeinfo = localtime(&_time);
                std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

                bcListLb.at(0).append({std::to_string(i+1), blocks[i].getBlockhash(), blocks[i].getPrevhash(), blocks[i].getTransaction().getClient(), blocks[i].getTransaction().getLocation(), std::to_string(blocks[i].getTransaction().getAmount()), buffer});
            }

            /// Para cerrar la vista correctamente
            bcListClose.create(*bcListWin, nana::rectangle(525,405, 50, 30));
            bcListClose.caption("Cerrar");
            bcListClose.events().click([this](){
                bcListLb.clear();
                bcListLb.clear_headers();
                bcListWin->close();
            });

            bcListWin->show();
        });

        add.create(*this, nana::rectangle(325,345, 150, 30));
        add.caption("Añadir transacción");
        add.events().click([this](){
            nana::inputbox::text _client("Nombre del cliente");
            nana::inputbox::text _location("Lugar de retiro");
            nana::inputbox::real _amount("Cantidad de dinero", 100, 1, 999, 1);

            nana::inputbox inputTransaction(*this, "Ingrese los datos de la transacción", "Añadir transacción");

            inputTransaction.verify([&_client, &_amount, &_location](nana::window handle){
                if(_client.value().empty() || _location.value().empty() || _amount.value() == 0.0){
                    nana::msgbox mb(handle, "Invalid input");
                    mb << "Ningún campo debe estar vacío, por favor complete los campos";
                    mb.show();
                    return false;
                }

                return true;
            });

            if(inputTransaction.show_modal(_client, _amount, _location)){
                Transaction _tr(_client.value(), _location.value(), _amount.value());
                _blockchain.addTransaction(_tr);

                nana::msgbox mb(*this, "Success!");
                mb << "La transacción ha sido añadida exitosamente!";
                mb.show();
            }
        });

        modify.create(*this, nana::rectangle(325,385, 150, 30));
        modify.caption("Modificar bloque");
        modify.events().click([this](){
            nana::inputbox::text _hash("Hash del bloque a modificar");
            nana::inputbox::text _client("Nombre del nuevo cliente");
            nana::inputbox::real _amount("Nueva cantidad de dinero", 0.0, 1, 999, 1);
            nana::inputbox::text _location("Nuevo lugar de retiro");

            nana::inputbox modifyTransaction(*this, "Ingrese los datos a modificar", "Modificar transacción");

            modifyTransaction.verify([&_hash](nana::window handle){
                if(_hash.value().empty()){
                    nana::msgbox mb(handle, "Invalid hash");
                    mb << "Por favor ingrese un hash válido";
                    mb.show();
                    return false;
                }

                return true;
            });

            if(modifyTransaction.show_modal(_hash ,_client, _amount, _location)){
                _blockchain.modifyTransaction(_hash.value(), _client.value(), _amount.value(), _location.value());

                nana::msgbox mb(*this, "Success!");
                mb << "La transacción ha sido modificada exitosamente! No se olvide de hacer el recálculo en cascada.";
                mb.show();
            }
        });

        erase.create(*this, nana::rectangle(325,425, 150, 30));
        erase.caption("Eliminar bloque");
        erase.events().click([this](){
            nana::inputbox::integer _index("Indice del bloque a eliminar", 0, 0, 99, 1);

            nana::inputbox eraseTransaction(*this, "Ingrese el indice del bloque a eliminar (indice = i-1)", "Eliminar transacción");

            int count = _blockchain.getBlockCount();

            eraseTransaction.verify([&_index, &count](nana::window handle){
                if(_index.value() < 0 || _index.value() > count){
                    nana::msgbox mb(handle, "Invalid index");
                    mb << "Ingrese un índice válido para el bloque a eliminar";
                    mb.show();

                    return false;
                }

                return true;
            });

            if(eraseTransaction.show_modal(_index)){
                _blockchain.deleteRecordatIndex(_index.value());

                nana::msgbox mb(*this, "Success!");
                mb << "El bloque ha sido eliminado exitosamente! No se olvide del recálculo en cascada";
                mb.show();
            }
        });

        recalculate.create(*this, nana::rectangle(325,465, 150, 30));
        recalculate.caption("Recálculo en cascada");
        recalculate.events().click([this](){
            _blockchain.cascadeRecalculation();

            nana::msgbox mb(*this, "Success!");
            mb << "La blockchain ha sido recalculada exitosamente!";
            mb.show();
        });

        back.create(*this, nana::rectangle(325,505, 150, 30));
        back.caption("Volver al menú principal");
        back.events().click([&](){
            this->close();
            backToMenu(_blockchain);
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

    /// Para los resultados de las busquedas
    nana::form* searchResults;
    nana::listbox searchLb;
    nana::button closeSearchs;

public:
    searchMenu(BlockChain& bc) : GUI(bc){
        direct.create(*this, nana::rectangle(325, 265, 150, 30));
        direct.caption("Búsqueda directa");
        direct.events().click([this](){
            nana::inputbox::text hash("Hash del bloque");
            nana::inputbox directSearch(*this, "Ingrese el hash del bloque", "Búsqueda directa");

            directSearch.verify([&hash](nana::window handle){
                if(hash.value().empty()){
                    nana::msgbox mb(handle, "Invalid input");
                    mb << "Por favor complete el campo requerido.";
                    mb.show();

                    return false;
                }

                return true;
            });

            if(directSearch.show_modal(hash)){
                searchResults = new nana::form(nana::API::make_center(600,280));
                searchResults->caption("Resultados de la búsqueda");

                searchLb.create(*searchResults, nana::rectangle(0,0, 600, 240));

                /// Headers de la lista
                searchLb.append_header("i", 20);
                searchLb.append_header("Client");
                searchLb.append_header("Location");
                searchLb.append_header("Amount");
                searchLb.append_header("Date");

                /// Realizar la búsqueda
                auto result = _blockchain.search(hash.value());

                /// Convertir time_t a fecha leible
                auto _date = result.getDate();
                char buffer[80];
                struct tm* timeinfo;
                timeinfo = localtime(&_date);
                std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

                searchLb.at(0).append({"1", result.getClient(), result.getLocation(), std::to_string(result.getAmount()), buffer});

                /// Para cerrar la vista correctamente
                closeSearchs.create(*searchResults, nana::rectangle(525,245, 50, 30));
                closeSearchs.caption("Cerrar");
                closeSearchs.events().click([this](){
                    searchLb.clear();
                    searchLb.clear_headers();
                    searchResults->close();
                });

                searchResults->show();
            }
        });

        range.create(*this, nana::rectangle(325,305, 150, 30));
        range.caption("Búsqueda por rango");
        range.events().click([this](){
            nana::inputbox::text begin("Hash inicial", "000000000000000000000000000000000000000000000000");
            nana::inputbox::text end("Hash final", "ffffffffffffffffffffffffffffffffffffffffffffffff");
            nana::inputbox rangeSearch(*this, "Ingrese el hash del bloque", "Búsqueda por rango");

            rangeSearch.verify([&begin, &end](nana::window handle){
                if(begin.value().empty() || end.value().empty()){
                    nana::msgbox mb(handle, "Invalid input");
                    mb << "Por favor complete los campos requeridos.";
                    mb.show();

                    return false;
                }

                return true;
            });

            if(rangeSearch.show_modal(begin, end)){
                searchResults = new nana::form(nana::API::make_center(600,280));
                searchResults->caption("Resultados de la búsqueda");

                searchLb.create(*searchResults, nana::rectangle(0,0, 600, 240));

                /// Headers de la lista
                searchLb.append_header("i", 20);
                searchLb.append_header("Client");
                searchLb.append_header("Location");
                searchLb.append_header("Amount");
                searchLb.append_header("Date");

                /// Realizar la búsqueda
                auto results = _blockchain.range_search(begin.value(), end.value());

                for(int i=0; i<results.size(); i++) {
                    /// Convertir time_t a fecha leible
                    auto _date = results[i].getDate();
                    char buffer[80];
                    struct tm *timeinfo;
                    timeinfo = localtime(&_date);
                    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

                    searchLb.at(0).append({std::to_string(i+1), results[i].getClient(), results[i].getLocation(), std::to_string(results[i].getAmount()), buffer});
                }

                /// Para cerrar la vista correctamente
                closeSearchs.create(*searchResults, nana::rectangle(525,245, 50, 30));
                closeSearchs.caption("Cerrar");
                closeSearchs.events().click([this](){
                    searchLb.clear();
                    searchLb.clear_headers();
                    searchResults->close();
                });

                searchResults->show();
            }
        });

        prefix.create(*this, nana::rectangle(325,345, 150, 30));
        prefix.caption("Búsqueda por prefijo");
        prefix.events().click([this](){
            nana::inputbox::text prefixStr("Hash del bloque", "0000");
            nana::inputbox prefixSearch(*this, "Ingrese el prefijo del hash", "Búsqueda por prefijo");

            prefixSearch.verify([&prefixStr](nana::window handle){
                if(prefixStr.value().empty()){
                    nana::msgbox mb(handle, "Invalid input");
                    mb << "Por favor complete el campo requerido.";
                    mb.show();

                    return false;
                }

                return true;
            });

            if(prefixSearch.show_modal(prefixStr)){
                searchResults = new nana::form(nana::API::make_center(600,280));
                searchResults->caption("Resultados de la búsqueda");

                searchLb.create(*searchResults, nana::rectangle(0,0, 600, 240));

                /// Headers de la lista
                searchLb.append_header("i", 20);
                searchLb.append_header("Client");
                searchLb.append_header("Location");
                searchLb.append_header("Amount");
                searchLb.append_header("Date");

                /// Realizar la búsqueda
                auto results = _blockchain.starts_with(prefixStr.value());

                for(int i=0; i<results.size(); i++) {
                    /// Convertir time_t a fecha leible
                    auto _date = results[i].getDate();
                    char buffer[80];
                    struct tm *timeinfo;
                    timeinfo = localtime(&_date);
                    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

                    searchLb.at(0).append({std::to_string(i+1), results[i].getClient(), results[i].getLocation(), std::to_string(results[i].getAmount()), buffer});
                }

                /// Para cerrar la vista correctamente
                closeSearchs.create(*searchResults, nana::rectangle(525,245, 50, 30));
                closeSearchs.caption("Cerrar");
                closeSearchs.events().click([this](){
                    searchLb.clear();
                    searchLb.clear_headers();
                    searchResults->close();
                });

                searchResults->show();
            }
        });

        pattern.create(*this, nana::rectangle(325,385, 150, 30));
        pattern.caption("Búsqueda por patrón");
        pattern.events().click([this](){
            nana::inputbox::text patternStr("Patrón del hash", "0000");
            nana::inputbox patternSearch(*this, "Ingrese el patrón del hash", "Búsqueda por patrón");

            patternSearch.verify([&patternStr](nana::window handle){
                if(patternStr.value().empty()){
                    nana::msgbox mb(handle, "Invalid input");
                    mb << "Por favor complete el campo requerido.";
                    mb.show();

                    return false;
                }

                return true;
            });

            if(patternSearch.show_modal(patternStr)){
                searchResults = new nana::form(nana::API::make_center(600,280));
                searchResults->caption("Resultados de la búsqueda");

                searchLb.create(*searchResults, nana::rectangle(0,0, 600, 240));

                /// Headers de la lista
                searchLb.append_header("i", 20);
                searchLb.append_header("Client");
                searchLb.append_header("Location");
                searchLb.append_header("Amount");
                searchLb.append_header("Date");

                /// Realizar la búsqueda
                auto results = _blockchain.contains(patternStr.value());

                for(int i=0; i<results.size(); i++) {
                    /// Convertir time_t a fecha leible
                    auto _date = results[i].getDate();
                    char buffer[80];
                    struct tm *timeinfo;
                    timeinfo = localtime(&_date);
                    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

                    searchLb.at(0).append({std::to_string(i+1), results[i].getClient(), results[i].getLocation(), std::to_string(results[i].getAmount()), buffer});
                }

                /// Para cerrar la vista correctamente
                closeSearchs.create(*searchResults, nana::rectangle(525,245, 50, 30));
                closeSearchs.caption("Cerrar");
                closeSearchs.events().click([this](){
                    searchLb.clear();
                    searchLb.clear_headers();
                    searchResults->close();
                });

                searchResults->show();
            }
        });

        max.create(*this, nana::rectangle(325,425, 150, 30));
        max.caption("Máximo valor (de hash)");
        max.events().click([this](){
            searchResults = new nana::form(nana::API::make_center(600,280));
            searchResults->caption("Resultados de la búsqueda");

            searchLb.create(*searchResults, nana::rectangle(0,0, 600, 240));

            /// Headers de la lista
            searchLb.append_header("i", 20);
            searchLb.append_header("Client");
            searchLb.append_header("Location");
            searchLb.append_header("Amount");
            searchLb.append_header("Date");

            /// Realizar la búsqueda
            auto result = _blockchain.max_value();

            /// Convertir time_t a fecha leible
            auto _date = result.getDate();
            char buffer[80];
            struct tm *timeinfo;
            timeinfo = localtime(&_date);
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

            searchLb.at(0).append({"1", result.getClient(), result.getLocation(), std::to_string(result.getAmount()), buffer});

            /// Para cerrar la vista correctamente
            closeSearchs.create(*searchResults, nana::rectangle(525,245, 50, 30));
            closeSearchs.caption("Cerrar");
            closeSearchs.events().click([this](){
                searchLb.clear();
                searchLb.clear_headers();
                searchResults->close();
            });

            searchResults->show();
        });

        min.create(*this, nana::rectangle(325,465, 150, 30));
        min.caption("Mínimo valor (de hash)");
        min.events().click([this](){
            searchResults = new nana::form(nana::API::make_center(600,280));
            searchResults->caption("Resultados de la búsqueda");

            searchLb.create(*searchResults, nana::rectangle(0,0, 600, 240));

            /// Headers de la lista
            searchLb.append_header("i", 20);
            searchLb.append_header("Client");
            searchLb.append_header("Location");
            searchLb.append_header("Amount");
            searchLb.append_header("Date");

            /// Realizar la búsqueda
            auto result = _blockchain.min_value();

            /// Convertir time_t a fecha leible
            auto _date = result.getDate();
            char buffer[80];
            struct tm *timeinfo;
            timeinfo = localtime(&_date);
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

            searchLb.at(0).append({"1", result.getClient(), result.getLocation(), std::to_string(result.getAmount()), buffer});

            /// Para cerrar la vista correctamente
            closeSearchs.create(*searchResults, nana::rectangle(525,245, 50, 30));
            closeSearchs.caption("Cerrar");
            closeSearchs.events().click([this](){
                searchLb.clear();
                searchLb.clear_headers();
                searchResults->close();
            });

            searchResults->show();
        });

        back.create(*this, nana::rectangle(325,505, 150, 30));
        back.caption("Volver al menú principal");
        back.events().click([&](){
            this->close();
            backToMenu(_blockchain);
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
    calculationsMenu(BlockChain& bc): GUI(bc){
        moneyOfClient.create(*this, nana::rectangle(300, 305, 175, 30));
        moneyOfClient.caption("Dinero recaudado por cliente");
        moneyOfClient.events().click([this](){
            nana::inputbox::text client("Nombre del cliente");
            nana::inputbox calculation(*this, "Ingrese el nombre del cliente", "Dinero por cliente");

            calculation.verify([&client](nana::window handle){
                if(client.value().empty()){
                    nana::msgbox mb(handle, "Invalid input");
                    mb << "Por favor complete el campo requerido";
                    mb.show();

                    return false;
                }

                return true;
            });

            if(calculation.show_modal(client)){
                auto result = _blockchain.calculateAmountPerClient(client.value());

                nana::msgbox displayResult(*this, "Resultado");
                displayResult << "El cliente que ha buscado se llama: " << client.value() << '\n';
                displayResult << "Dicho cliente ha recaudado: " << std::to_string(result) << " soles";

                displayResult.show();
            }
        });

        moneyOfPlace.create(*this, nana::rectangle(300,345, 175, 30));
        moneyOfPlace.caption("Dinero movido en lugar");
        moneyOfPlace.events().click([this](){
            nana::inputbox::text location("Nombre del cliente");
            nana::inputbox calculation(*this, "Ingrese el nombre del lugar", "Dinero por cliente");

            calculation.verify([&location](nana::window handle){
                if(location.value().empty()){
                    nana::msgbox mb(handle, "Invalid input");
                    mb << "Por favor complete el campo requerido";
                    mb.show();

                    return false;
                }

                return true;
            });

            if(calculation.show_modal(location)){
                auto result = _blockchain.calculateAmountPerLocation(location.value());

                nana::msgbox displayResult(*this, "Resultado");
                displayResult << "El lugar que ha buscado está en: " << location.value() << '\n';
                displayResult << "Dicho lugar ha movido: " << std::to_string(result) << " soles";

                displayResult.show();
            }
        });

        richestClient.create(*this, nana::rectangle(287,385, 200, 30));
        richestClient.caption("Cliente con más dinero recaudado");
        richestClient.events().click([this](){
            auto result = _blockchain.getRichestClient();

            nana::msgbox displayResult(*this, "Resultado");
            displayResult << "El cliente más rico es: " << result;

            displayResult.show();
        });

        richestLocation.create(*this, nana::rectangle(300,425, 175, 30));
        richestLocation.caption("Lugar con más dinero movido");
        richestLocation.events().click([this](){
            auto result = _blockchain.getRichestLocation();

            nana::msgbox displayResult(*this, "Resultado");
            displayResult << "El lugar donde han movido más dinero es: " << result;

            displayResult.show();
        });

        back.create(*this, nana::rectangle(300,465, 175, 30));
        back.caption("Volver al menú principal");
        back.events().click([&](){
            this->close();
            backToMenu(_blockchain);
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
    mainMenu(BlockChain& bc) : GUI(bc){
        blockchain.create(*this, nana::rectangle(325, 305, 150, 30));
        blockchain.caption("Mi Blockchain");
        blockchain.events().click([&](){
            this->close();
            bcMenu(_blockchain).open();
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
                _blockchain.loadFromCSV(path.value());

                nana::msgbox mb(*this, "Success!");
                mb << "El CSV ha sido cargado exitosamente!";
                mb.show();
            }
        });

        search.create(*this, nana::rectangle(325,385, 150, 30));
        search.caption("Criterios de búsqueda");
        search.events().click([&](){
            this->close();
            searchMenu(_blockchain).open();
        });

        calculations.create(*this, nana::rectangle(325,425, 150, 30));
        calculations.caption("Cálculos Transaccionales");
        calculations.events().click([&](){
            this->close();
            calculationsMenu(_blockchain).open();
        });

        quit.create(*this, nana::rectangle(325,465, 150, 30));
        quit.caption("Cerrar aplicación");
        quit.events().click(nana::API::exit);
    }
};

/// Hack para volver al menu
void backToMenu(BlockChain& bc){
    mainMenu(bc).open();
}

#endif //MENU_H