#include "app/utils.hpp"
#include <iomanip>
#include <sstream>

namespace App {
    namespace Utils {

    void banner() {
        std::cout << "=== Demo Abstraccion & Modularidad con Funciones (C++) ===\n";
    }

    void printLine(const std::string& msg) {
        std::cout << msg << "\n";
    }

    int callCounter() {
        // Ámbito de función: 'static' vive entre invocaciones, visible sólo aquí :contentReference[oaicite:16]{index=16}
        static int counter = 0;
        return ++counter;
    }

    std::string join(const std::vector<std::string>& parts, const std::string& sep) {
        std::ostringstream oss;
        for (std::size_t i = 0; i < parts.size(); ++i) {
            if (i) oss << sep;
            oss << parts[i];
        }
        return oss.str();
    }

    std::string toFixed(double v, int decimals) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(decimals) << v;
        return oss.str();
    }

    } // namespace Utils
} // namespace App
