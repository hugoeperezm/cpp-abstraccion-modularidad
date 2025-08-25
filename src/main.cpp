#include "app/utils.hpp"
#include "app/inventory.hpp"
#include "app/pricing.hpp"
#include "app/analytics.hpp"

#include <iostream>
#include <vector>
#include <string>

namespace App {
// Ámbito del espacio de nombres + “global” del programa (dentro de App) :contentReference[oaicite:25]{index=25}
inline const std::string kAppName = "Retail Demo";

} // namespace App

int main() {
    using namespace App::Utils;
    using App::kAppName;

    banner();
    printLine("Aplicacion: " + kAppName);

    // Ámbito local: 'ventas' sólo es visible dentro de main (bloque/función) :contentReference[oaicite:26]{index=26}
    std::vector<double> ventas = { 1200000, 240000, 320000, 910000, 600000, 450000 };

    // Llamadas a funciones (flujo): prototipos están en headers, definiciones en src/ :contentReference[oaicite:27]{index=27}
    printLine("Mean(ventas) = " + toFixed(App::Analytics::mean(ventas)));

    auto ma = App::Analytics::movingAverage(ventas, 3);
    printLine("MA(3) size = " + std::to_string(ma.size()));

    // Inventario semilla
    auto inv = App::Inventory::seed();

    // Pedido (por valor): construcción de líneas
    std::vector<App::Pricing::Line> order = {
        {"SKU-001", 2}, {"SKU-004", 1}, {"SKU-002", 3}
    };

    // Lista de precios (sku, unitPrice)
    std::vector<std::pair<std::string,double>> priceList = {
        {"SKU-001", 210000.0}, {"SKU-002", 150000.0}, {"SKU-004", 300000.0}
    };

    std::vector<App::Pricing::PricedLine> priced;
    bool ok = App::Pricing::priceLines(order, priceList, priced); // bool de validación, salida por ref
    if (!ok) {
        printLine("Error al valuar lineas del pedido.");
        return 1;
    }

    // Mostrar subtotal vs modificación por referencia
    const double sub = App::Pricing::subtotal(priced); // por valor (no muta) :contentReference[oaicite:28]{index=28}
    printLine("Subtotal: $" + toFixed(sub));

    // Aplicar descuento por fidelidad y luego impuesto (IVA del namespace Utils) :contentReference[oaicite:29]{index=29}
    const int loyaltyTier = 4; // simular cliente leal
    const double total = App::Pricing::grandTotal(priced, loyaltyTier, App::Utils::kIvaColombia);
    printLine("Total con IVA y descuento (tier 4): $" + toFixed(total));

    // Demostración paso por referencia: reducir stock original (muta inventario) :contentReference[oaicite:30]{index=30}
    for (const auto& l : order) {
        if (!App::Inventory::reduceStock(inv, l.sku, l.units)) {
            printLine("No hay stock suficiente para " + l.sku);
        }
    }

    // Demostración punteros (& en llamada y * en función) según el documento :contentReference[oaicite:31]{index=31}
    int totalUnitsPicked = 0;
    for (const auto& l : order) {
        App::Inventory::unitsPickedTotal_add(&totalUnitsPicked, l.units);
    }
    printLine("Unidades alistadas (punteros): " + std::to_string(totalUnitsPicked));

    // Ámbito de función: contador estático que recuerda llamadas
    printLine("callCounter() -> " + std::to_string(callCounter()));
    printLine("callCounter() -> " + std::to_string(callCounter()));
    printLine("callCounter() -> " + std::to_string(callCounter()));

    // Flujo de ejecución: recursiveSum (muestra return de caso base/recursivo) :contentReference[oaicite:32]{index=32}
    double s = App::Analytics::recursiveSum(ventas);
    printLine("Suma recursiva de ventas: $" + toFixed(s));

    // Mostrar líneas con precios (ámbito de clase/struct implícito en PricedLine)
    printLine("--- Lineas valuadas ---");
    for (const auto& pl : priced) {
        printLine("SKU: " + pl.sku + " U:" + std::to_string(pl.units) +
                  " P: $" + toFixed(pl.unitPrice) + " Total: $" + toFixed(pl.lineTotal));
    }

    // Buscar item (por valor: regresa copia opcional sin mutar) :contentReference[oaicite:33]{index=33}
    auto found = App::Inventory::findBySku(inv, "SKU-001");
    if (found) {
        printLine("Stock restante de " + found->sku + ": " + std::to_string(found->stock));
    }

    printLine("OK.");
    return 0;
}
