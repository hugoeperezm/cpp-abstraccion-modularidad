#include "app/inventory.hpp"
#include <algorithm>

namespace App {
    namespace Inventory {

    std::vector<Item> seed() {
        return {
            {"SKU-001", "Teclado Mecánico", 25, 210000.0},
            {"SKU-002", "Mouse Ergonomico", 40, 150000.0},
            {"SKU-003", "Monitor 27\"",     10, 1200000.0},
            {"SKU-004", "Dock USB-C",       30, 300000.0}
        };
    }

    std::optional<Item> findBySku(const std::vector<Item>& inv, const std::string& sku) {
        auto it = std::find_if(inv.begin(), inv.end(), [&](const Item& it){ return it.sku == sku; });
        if (it == inv.end()) return std::nullopt;
        return *it; // por valor: copia segura (no muta original) :contentReference[oaicite:17]{index=17}
    }

    bool reduceStock(std::vector<Item>& inv, const std::string& sku, int units) {
        for (auto& it : inv) {
            if (it.sku == sku) {
                if (it.stock >= units) {
                    it.stock -= units;    // por referencia: muta el original :contentReference[oaicite:18]{index=18}
                    return true;
                }
                return false;
            }
        }
        return false;
    }

    void unitsPickedTotal_add(int* totalUnits, int unitsToAdd) {
        // Demostración puntero: según el documento, la función usa * y el llamador pasa &var :contentReference[oaicite:19]{index=19}
        if (totalUnits) {
            *totalUnits += unitsToAdd;
        }
    }

    } // namespace Inventory
} // namespace App
