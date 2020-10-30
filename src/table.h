#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <iostream>


template<typename T>
class Table;

namespace {
    inline size_t pos_mod(int n, int mod) {
        return (n % mod + mod) % mod;
    }

    template<typename T>
    class LineProxy {
        public:
            using RefTable = Table<T>;


            LineProxy(RefTable* table, size_t line):
                _table(table),
                _line(line)
            {}

            LineProxy(RefTable& table, size_t line): LineProxy(&table, line) {}

            class Iterator {
                public:
                    Iterator(RefTable* table, size_t index):
                        _table(table),
                        _index(index)
                    {}
                    Iterator(RefTable& table, size_t index): Iterator(&table, index) {}

                    Iterator& operator++() {
                        ++_index;
                        return *this;
                    }

                    Iterator operator++(int) {
                        Iterator it(_table, _index);
                        ++_index;
                        return it;
                    }

                    bool operator==(const Iterator& it) {
                        return _index == it._index;
                    }

                    bool operator!=(const Iterator& it) {
                        return _index != it._index;
                    }

                    T& operator* ()
                    {
                        return _table->at(_index);
                    }

                    T* operator->() {
                        return &**this;
                    }
                private:
                    size_t _index;
                    RefTable* _table;
            };

            Iterator begin() {
                return Iterator(_table, _line * _table->getWidth());
            }

            Iterator end() {
                return Iterator(_table, (_line + 1) * _table->getWidth());
            }

            T& at(size_t index) {
                return _table->at(_line, index);
            }
        private:
            const size_t _line;
            RefTable* _table;
    };


    template<typename T>
    class ColumnProxy {
        public:
            using RefTable = Table<T>;


            ColumnProxy(RefTable* table, size_t col):
                _table(table),
                _col(col)
            {}

            ColumnProxy(RefTable& table, size_t col): ColumnProxy(&table, col) {}

            class Iterator {
                public:
                    Iterator(RefTable* table, size_t index):
                        _table(table),
                        _index(index)
                    {}
                    Iterator(RefTable& table, size_t index): Iterator(&table, index) {}

                    Iterator& operator++() {
                        _index += _table->getWidth();
                        return *this;
                    }

                    Iterator operator++(int) {
                        Iterator it(_table, _index);
                        _index += _table->getWidth();
                        return it;
                    }

                    bool operator==(const Iterator& it) const {
                        return _index == it._index;
                    }

                    bool operator!=(const Iterator& it) const {
                        return _index != it._index;
                    }

                    T& operator* ()
                    {
                        return _table->at(_index);
                    }

                    T* operator->() {
                        return &**this;
                    }
                private:
                    size_t _index;
                    RefTable* _table;
            };

            Iterator begin() {
                return Iterator(_table, _col);
            }

            Iterator end() {
                return Iterator(_table, (_table->getHeight()) * _table->getWidth() + _col);
            }

            T& at(size_t index) {
                return _table->at(index, _col);
            }
        private:
            const size_t _col;
            RefTable* _table;
    };

    template<typename T>
    class LineIterator {
        public:
            using RefTable = Table<T>;

            LineIterator(RefTable* table, size_t index):
                _table(table),
                _index(index)
            {}
            LineIterator(RefTable& table, size_t index): LineIterator(&table, index) {}

            LineIterator& operator++() {
                ++_index;
                return *this;
            }

            LineIterator operator++(int) {
                LineIterator it(_table, _index);
                ++_index;
                return it;
            }

            bool operator==(const LineIterator& it) const {
                return _index == it._index;
            }

            bool operator!=(const LineIterator& it) const {
                return _index != it._index;
            }

            LineProxy<T> operator* ()
            {
                return _table->line(_index);
            }

            LineProxy<T>* operator->() {
                return &**this;
            }
        private:
            size_t _index;
            RefTable* _table;
    };

    template<typename T>
    class ColumnIterator {
        public:
            using RefTable = Table<T>;

            ColumnIterator(RefTable* table, size_t index):
                _table(table),
                _index(index)
            {}
            ColumnIterator(RefTable& table, size_t index): ColumnIterator(&table, index) {}

            ColumnIterator& operator++() {
                ++_index;
                return *this;
            }

            ColumnIterator operator++(int) {
                ColumnIterator it(_table, _index);
                ++_index;
                return it;
            }

            bool operator==(const ColumnIterator& it) const {
                return _index == it._index;
            }

            bool operator!=(const ColumnIterator& it) const {
                return _index != it._index;
            }

            ColumnProxy<T> operator* ()
            {
                return _table->col(_index);
            }

            ColumnProxy<T>* operator->() {
                return &**this;
            }
        private:
            size_t _index;
            RefTable* _table;
    };

    template<typename T>
    class Lines {
        public:
            using RefTable = Table<T>;

            Lines(RefTable* table):
                _table(table)
            {}
            Lines(RefTable& table): Lines(&table) {}

            LineIterator<T> begin() {
                return LineIterator<T>(_table, 0);
            }

            LineIterator<T> end() {
                return LineIterator<T>(_table, _table->getHeight());
            }
        private:
            RefTable* _table;
    };

    template<typename T>
    class Columns {
        public:
            using RefTable = Table<T>;

            Columns(RefTable* table):
                _table(table)
            {}
            Columns(RefTable& table): Columns(&table) {}


            ColumnIterator<T> begin() {
                return ColumnIterator<T>(_table, 0);
            }

            ColumnIterator<T> end() {
                return ColumnIterator<T>(_table, _table->getWidth());
            }
        private:
            RefTable* _table;
    };

}




template<typename T>
class Table {

    using Data = std::vector<T>;

    public:
        Table(size_t width, size_t height, const T& value = T()):
            WIDTH(width),
            HEIGHT(height),
            m_data(width * height, value) {

        }

        typename Data::iterator begin() {
            return m_data.begin();
        }

        typename Data::iterator end() {
            return m_data.end();
        }

        Lines<T> lines() {
            return Lines<T>(this);
        }
        
        Columns<T> columns() {
            return Columns<T>(this);
        }

        LineProxy<T> line(size_t index) {
            return LineProxy<T>(this, index);
        }
        
        ColumnProxy<T> col(size_t index) {
            return ColumnProxy<T>(this, index);
        }

        T& at(size_t index) {
            return m_data.at(index);
        }

        const T& at(size_t index) const {
            return m_data.at(index);
        }

        T& at(size_t row, size_t line) {
            return at(index(row % WIDTH, line % HEIGHT));
        }

        const T& at(size_t row, size_t line) const {
            return at(row, line);
        }

        T& at(int row, int line) {
            return at(index(row, line));
        }

        const T& at(int row, int line) const {
            return at(row, line);
        }

        size_t index(size_t row, size_t line) const {
            return row + WIDTH * line;
        }

        size_t index(int row, int line) const {
            return index(pos_mod(row, WIDTH), pos_mod(line, HEIGHT));
        }

        std::pair<size_t, size_t> coord(size_t index) const {
            size_t y = index / getWidth();
            size_t x = index % getWidth();
            return std::make_pair(x, y);
        }

        size_t size() const {
            return m_data.size();
        }

        size_t getWidth() const {
            return WIDTH;
        }

        size_t getHeight() const {
            return HEIGHT;
        }

    private:
        const size_t HEIGHT;
        const size_t WIDTH;
        Data m_data;

};


#endif // TABLE_H