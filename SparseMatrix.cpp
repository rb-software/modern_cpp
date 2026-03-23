#include <iostream>
#include <unordered_map>

// Unordered map requires custom hash function for the key type, which in this case is std::pair<size_t, size_t>
struct PairHash
{
    std::size_t operator()(const std::pair<size_t, size_t>& p) const
    {
        return std::hash<size_t>()(p.first) ^ (std::hash<size_t>()(p.second));
    }
};

// SparseMatrix class definition
class SparseMatrix
{
public:
    // Delete the default constructor to prevent creating a sparse matrix without specifying dimensions
    SparseMatrix() = delete;

    explicit SparseMatrix(size_t rows, size_t cols) 
        : m_rows(rows)
        , m_cols(cols)
    {
        std::cout << "SparseMatrix created with size: " << rows << "x" << cols << std::endl;
    }

    // Setter
    void set(size_t r, size_t c , int value)
    {
        if (value != 0)
        {
            m_data[{r, c}] = value;
        }
        else
        {
            // If the value is zero, we can remove the entry from the map to save space
            m_data.erase({r, c});
        }
    }

    // Getter
    int get(size_t r, size_t c) const
    {
        // Find element in the map
        auto it = m_data.find({r, c});

        if (it != m_data.end())
        {
            return it->second;
        }
        return 0;
    }
 
private:
    // Class member variables
    std::unordered_map<std::pair<size_t, size_t>, int, PairHash> m_data; 
    size_t m_rows;
    size_t m_cols;
};

int main() 
{
    // Create a sparse matrix of size 256x256
    SparseMatrix matrix(256, 256);

    // Example of setting values in the sparse matrix
    matrix.set(0, 0, 5);
    matrix.set(1, 2, 10);

    // Example of getting values from the sparse matrix
    std::cout << "Value at (0, 0): " << matrix.get(0, 0) << std::endl; // Should print 5
    std::cout << "Value at (1, 2): " << matrix.get(1, 2) << std::endl; // Should print 10

    // Create another sparse matrix of size 16x16
    SparseMatrix matrix2(16, 16);
    matrix2.set(0, 0, 20);
    matrix2.set(1, 1, 30);

    // Example of getting values from the second sparse matrix
    std::cout << "Value at (0, 0): " << matrix2.get(0, 0) << std::endl; // Should print 20
    std::cout << "Value at (1, 1): " << matrix2.get(1, 1) << std::endl; // Should print 30

    return 0;
}