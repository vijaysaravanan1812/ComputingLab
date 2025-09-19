#include <string>
#include <unordered_map>
#include <cctype> // Required for isdigit

/**
 * @class Spreadsheet
 * @brief Implements a sparse spreadsheet with basic cell manipulation and formula evaluation.
 *
 * This class uses an unordered_map for sparse storage, meaning it only allocates
 * memory for cells that have been assigned a non-zero value. This approach is
 * highly efficient and avoids the "Time Limit Exceeded" issue seen with
 * pre-allocating the entire grid.
 */
class Spreadsheet {
private:
    // A hash map to store cell values. The key is the cell name (e.g., "A1")
    // and the value is the integer stored in that cell.
    std::unordered_map<std::string, int> cell_storage;

    /**
     * @brief Resolves an operand string into its corresponding integer value.
     * @param operand A string that is either a literal number (e.g., "123")
     * or a cell reference (e.g., "B2").
     * @return The integer value of the operand.
     */
    int resolveValue(const std::string& operand) {
        // Based on problem constraints, if the first character is a digit,
        // we can safely assume the entire string is a literal number.
        if (!operand.empty() && isdigit(operand[0])) {
            return std::stoi(operand);
        }

        // Otherwise, the operand is a cell reference. We look for it in our storage.
        // The .find() method is an efficient way to check for key existence.
        auto it = cell_storage.find(operand);
        if (it != cell_storage.end()) {
            // The cell was found, so we return its stored value.
            return it->second;
        }

        // If the cell is not found in storage, its value is 0 by definition.
        return 0;
    }

public:
    /**
     * @brief Constructs the Spreadsheet.
     * @param rows The number of rows, as required by the problem signature.
     * Note: The constructor is intentionally left empty for performance.
     */
    Spreadsheet(int rows) {
        // No pre-initialization is needed. An empty map correctly represents
        // a grid where all cell values are implicitly 0.
    }

    /**
     * @brief Sets the value of a specific cell.
     * @param cell The name of the cell (e.g., "A1").
     * @param value The integer value to assign to the cell.
     */
    void setCell(const std::string& cell, int value) {
        cell_storage[cell] = value;
    }

    /**
     * @brief Resets the value of a specific cell back to 0.
     * @param cell The name of the cell to reset (e.g., "C5").
     */
    void resetCell(const std::string& cell) {
        // We can simply set the value to 0. If the cell didn't exist,
        // this will create it with a value of 0, which is functionally equivalent.
        // An alternative is to erase the key: cell_storage.erase(cell);
        cell_storage[cell] = 0;
    }

    /**
     * @brief Evaluates a formula which is guaranteed to be in the format "=X+Y".
     * @param formula The formula string to evaluate.
     * @return The integer result of the addition.
     */
    int getValue(const std::string& formula) {
        // The problem guarantees the format "=X+Y". We can find the '+'
        // to efficiently separate the two operands.
        // We start searching from index 1 to skip the leading '='.
        size_t operator_pos = formula.find('+', 1);

        // Extract the substrings for the left and right operands.
        std::string left_operand = formula.substr(1, operator_pos - 1);
        std::string right_operand = formula.substr(operator_pos + 1);

        // Resolve each operand to its value and return their sum.
        return resolveValue(left_operand) + resolveValue(right_operand);
    }
};

/**
 * Example Usage:
 * Spreadsheet* obj = new Spreadsheet(3);
 * obj->setCell("A1", 10);
 * int result = obj->getValue("=A1+5"); // result will be 15
 */
