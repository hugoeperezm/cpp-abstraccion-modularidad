#include "app/pricing.hpp"
#include "app/utils.hpp"
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

namespace App {
    namespace Pricing {

    double subtotal(const std::vector<PricedLine>& lines) {
        double s = 0.0;
        for (const auto& l : lines) s += l.lineTotal;
        return s; // devolución de resultado por return :contentReference[oaicite:20]{index=20}
    }

    void applyTax(double net, double taxRate, double& totalOut) {
        // Por referencia: escribe el resultado en el argumento de salida :contentReference[oaicite:21]{index=21}
        totalOut = net * (1.0 + taxRate);
    }

    bool priceLines(const std::vector<Line>& order,
                    const std::vector<std::pair<std::string,double>>& priceList,
                    std::vector<PricedLine>& outPricedLines) {
        std::unordered_map<std::string,double> map;
        for (auto& p : priceList) map.emplace(p.first, p.second);

        outPricedLines.clear();
        for (const auto& l : order) {
            auto it = map.find(l.sku);
            if (it == map.end() || l.units <= 0) return false;
            const double up = it->second;
            outPricedLines.push_back({l.sku, l.units, up, up * l.units});
        }
        return true;
    }

    double loyaltyDiscount(double amount, int loyaltyTier) {
        // Ejemplo simple por niveles
        double rate = 0.0;
        if      (loyaltyTier >= 5) rate = 0.12;
        else if (loyaltyTier >= 3) rate = 0.06;
        else if (loyaltyTier >= 1) rate = 0.02;
        return amount * (1.0 - rate);
    }

    double grandTotal(const std::vector<PricedLine>& priced,
                    int loyaltyTier,
                    double taxRate) {
        using namespace App::Utils;
        const double sub = subtotal(priced);      // composición de funciones (abstracción) :contentReference[oaicite:22]{index=22}
        const double afterDiscount = loyaltyDiscount(sub, loyaltyTier);
        double total = 0.0;
        applyTax(afterDiscount, taxRate, total);  // parámetro por referencia para salida :contentReference[oaicite:23]{index=23}
        return total;
    }

    } // namespace Pricing
} // namespace App
