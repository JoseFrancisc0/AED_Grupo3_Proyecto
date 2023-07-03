#ifndef MENU_H
#define MENU_H

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
using namespace nana;

void mainMenu(); // Forward Declarator

void searchMenu(){
    /// Window
    form fm(rectangle(0,0,800,600));
    fm.caption("BlockChain App");
    fm.bgcolor(colors::alice_blue);

    /// Header
    label header(fm, rectangle(0,0,800,50));
    header.format(true);
    header.bgcolor(colors::dark_blue);

    /// Title
    label title(fm, rectangle(200,5,400,40));
    title.format(true);
    title.caption("<size = 25 red font=\"Consolas\"> BlockChain App");
    title.text_align(align::center, align_v::center);
    title.bgcolor(colors::aquamarine);

    /// Buttons
    button directSearch(fm, rectangle(325,265, 150, 30));
    directSearch.caption("Búsqueda directa");
    directSearch.events().click(API::exit);

    button rangeSearch(fm, rectangle(325,305, 150, 30));
    rangeSearch.caption("Búsqueda por rango");
    rangeSearch.events().click(API::exit);

    button prefixSearch(fm, rectangle(325,345, 150, 30));
    prefixSearch.caption("Búsqueda por prefijo");
    prefixSearch.events().click(API::exit);

    button suffixSearch(fm, rectangle(325,385, 150, 30));
    suffixSearch.caption("Búsqueda por patrón");
    suffixSearch.events().click(API::exit);

    button minValue(fm, rectangle(325,425, 150, 30));
    minValue.caption("Valor máximo de hash");
    minValue.events().click(API::exit);

    button maxValue(fm, rectangle(325,465, 150, 30));
    maxValue.caption("Valor mínimo de hash");
    maxValue.events().click(API::exit);

    button back(fm,rectangle(325,505, 150, 30));
    back.caption("Volver al menú");
    back.events().click([&](){
        fm.hide();
        mainMenu();
    });

    /// Footnote
    label foot(fm, rectangle(0,550,800,50));
    foot.format(true);
    foot.bgcolor(colors::dark_blue);

    fm.show();
    exec();
}

void calculationsMenu(){
    /// Window
    form fm(rectangle(0,0,800,600));
    fm.caption("BlockChain App");
    fm.bgcolor(colors::alice_blue);

    /// Header
    label header(fm, rectangle(0,0,800,50));
    header.format(true);
    header.bgcolor(colors::dark_blue);

    /// Title
    label title(fm, rectangle(200,5,400,40));
    title.format(true);
    title.caption("<size = 25 red font=\"Consolas\"> BlockChain App");
    title.text_align(align::center, align_v::center);
    title.bgcolor(colors::aquamarine);

    /// Buttons
    button getRichestClient(fm, rectangle(325,265, 200, 30));
    getRichestClient.caption("Obtener el cliente con más dinero");
    getRichestClient.events().click(API::exit);

    button getRichestLocation(fm, rectangle(325,305, 200, 30));
    getRichestLocation.caption("Obtener el lugar con más dinero");
    getRichestLocation.events().click(API::exit);

    button moneyPerClient(fm, rectangle(325,345, 200, 30));
    moneyPerClient.caption("Obtener dinero recaudado por cliente");
    moneyPerClient.events().click(API::exit);

    button moneyPerLocation(fm, rectangle(325,385, 200, 30));
    moneyPerLocation.caption("Obtener dinero movido en lugar");
    moneyPerLocation.events().click(API::exit);

    button back(fm, rectangle(325,425, 200, 30));
    back.caption("Volver al menú");
    back.events().click([&](){
        fm.hide();
        mainMenu();
    });

    /// Footnote
    label foot(fm, rectangle(0,550,800,50));
    foot.format(true);
    foot.bgcolor(colors::dark_blue);

    fm.show();
    exec();
}

void bcMenu(){
    /// Window
    form fm(rectangle(0,0,800,600));
    fm.caption("BlockChain App");
    fm.bgcolor(colors::alice_blue);

    /// Header
    label header(fm, rectangle(0,0,800,50));
    header.format(true);
    header.bgcolor(colors::dark_blue);

    /// Title
    label title(fm, rectangle(200,5,400,40));
    title.format(true);
    title.caption("<size = 25 red font=\"Consolas\"> BlockChain App");
    title.text_align(align::center, align_v::center);
    title.bgcolor(colors::aquamarine);

    /// Buttons
    button add(fm, rectangle(325,305, 150, 30));
    add.caption("Añadir Transacción");
    add.events().click(API::exit);

    button get(fm, rectangle(325,345, 150, 30));
    get.caption("Ver Blockchain");
    get.events().click(API::exit);

    button modify(fm, rectangle(325,385, 150, 30));
    modify.caption("Modificar Transacción");
    modify.events().click(API::exit);

    button erase(fm, rectangle(325,425, 150, 30));
    erase.caption("Eliminar Bloque");
    erase.events().click(API::exit);

    button cascade(fm, rectangle(325,465, 150, 30));
    cascade.caption("Recálculo en cascada");
    cascade.events().click(API::exit);

    button back(fm, rectangle(325,505, 150, 30));
    back.caption("Volver al menú");
    back.events().click([&](){
        fm.hide();
        mainMenu();
    });

    /// Footnote
    label foot(fm, rectangle(0,550,800,50));
    foot.format(true);
    foot.bgcolor(colors::dark_blue);

    fm.show();
    exec();
}

void mainMenu(){
    /// Window
    form fm(rectangle(0,0,800,600));
    fm.caption("BlockChain App");
    fm.bgcolor(colors::alice_blue);

    /// Header
    label header(fm, rectangle(0,0,800,50));
    header.format(true);
    header.bgcolor(colors::dark_blue);

    /// Title
    label title(fm, rectangle(200,5,400,40));
    title.format(true);
    title.caption("<size = 25 red font=\"Consolas\"> BlockChain App");
    title.text_align(align::center, align_v::center);
    title.bgcolor(colors::aquamarine);

    /// Small graphics
    drawing dw{fm};
    dw.draw([](paint::graphics& graph) {
        graph.rectangle(rectangle(150,125,100,100), true, colors::light_coral);
        graph.rectangle(rectangle(350,125,100,100), true, colors::light_coral);
        graph.rectangle(rectangle(550,125,100,100), true, colors::light_coral);
    });

    /// Buttons
    button BC(fm, rectangle(325,305, 150, 30));
    BC.caption("Mi Blockchain");
    BC.events().click([&](){
        fm.hide();
        bcMenu();
    });

    button load(fm, rectangle(325,345, 150, 30));
    load.caption("Cargar CSV");
    load.events().click(API::exit);

    button searches(fm, rectangle(325,385, 150, 30));
    searches.caption("Criterios de búsqueda");
    searches.events().click([&](){
        fm.hide();
        searchMenu();
    });

    button calculos(fm, rectangle(325,425, 150, 30));
    calculos.caption("Cálculos Transaccionales");
    calculos.events().click([&](){
        fm.hide();
        calculationsMenu();
    });

    button quit(fm, rectangle(325,465, 150, 30));
    quit.caption("Cerrar aplicación");
    quit.events().click(API::exit);

    /// Footnote
    label foot(fm, rectangle(0,550,800,50));
    foot.format(true);
    foot.bgcolor(colors::dark_blue);

    fm.show();
    exec();
}


#endif //MENU_H