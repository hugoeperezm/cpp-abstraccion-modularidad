#include "app/analytics.hpp"
#include <stdexcept>

namespace App {
    namespace Analytics {

    double mean(const std::vector<double>& xs) {
        if (xs.empty()) return 0.0;
        double acc = 0.0;
        for (double v : xs) acc += v;
        return acc / xs.size();
    }

    double recursiveSum(const std::vector<double>& xs, std::size_t i) {
        // Flujo de llamada/retorno: caso base + caso recursivo :contentReference[oaicite:24]{index=24}
        if (i >= xs.size()) return 0.0;
        return xs[i] + recursiveSum(xs, i + 1);
    }

    std::vector<double> movingAverage(const std::vector<double>& xs, int window) {
        if (window <= 0) throw std::invalid_argument("window must be > 0");
        std::vector<double> out;
        if (xs.empty() || window > (int)xs.size()) return out;
        double acc = 0.0;
        for (int i = 0; i < window; ++i) acc += xs[i];
        out.push_back(acc / window);
        for (int i = window; i < (int)xs.size(); ++i) {
            acc += xs[i] - xs[i - window];
            out.push_back(acc / window);
        }
        return out;
    }

    } // namespace Analytics
} // namespace App
