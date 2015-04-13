/* ==============================================================
bstone: A source port of Blake Stone: Planet Strike

Copyright (c) 1992-2013 Apogee Entertainment, LLC
Copyright (c) 2013 Boris Bendovsky (bibendovsky@hotmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
============================================================== */


//
// A binary reader for a block of memory.
//


#ifndef BSTONE_MEMORY_BINARY_READER_INCLUDED
#define BSTONE_MEMORY_BINARY_READER_INCLUDED


#include <cstdint>


namespace bstone {


// A binary reader for a block of memory.
class MemoryBinaryReader {
public:
    MemoryBinaryReader();

    MemoryBinaryReader(
        const void* data,
        int64_t data_size);


    // Opens the reader.
    bool open(
        const void* data,
        int64_t data_size);

    // Closes the reader.
    void close();

    // Returns true if the reader is initialized or
    // false otherwise.
    bool is_initialized() const;

    // Reads a signed 8-bit integer value.
    int8_t read_s8();

    // Reads an unsigned 8-bit integer value.
    uint8_t read_u8();

    // Reads a signed 16-bit integer value.
    int16_t read_s16();

    // Reads an unsigned 16-bit integer value.
    uint16_t read_u16();

    // Reads a signed 32-bit integer value.
    int32_t read_s32();

    // Reads an unsigned 32-bit integer value.
    uint32_t read_u32();

    // Reads a signed 64-bit integer value.
    int64_t read_s64();

    // Reads an unsigned 64-bit integer value.
    uint64_t read_u64();

    // Reads a 32-bit float-point value.
    float read_r32();

    // Reads a 64-bit float-point value.
    double read_r64();

    // Skips a specified number of octets forward if count positive
    // or backward otherwise.
    bool skip(
        int64_t count);

    // Returns a current position.
    int64_t get_position() const;

    // Sets a current position to a specified one.
    bool set_position(
        int64_t position);

    // Returns a pointer to data for a current position.
    template<typename T>
    const T* get_data() const
    {
        return reinterpret_cast<const T*>(&data_[data_offset_]);
    }

private:
    const uint8_t* data_;
    int64_t data_size_;
    int64_t data_offset_;

    template<typename T>
    T read()
    {
        if (!is_initialized()) {
            return 0;
        }

        if (data_offset_ < 0) {
            return 0;
        }

        if ((data_offset_ + static_cast<int64_t>(sizeof(T))) >= data_size_) {
            return 0;
        }

        T result = *reinterpret_cast<const T*>(&data_[data_offset_]);
        data_offset_ += sizeof(T);
        return result;
    }
}; // MemoryBinaryReader


} // bstone


#endif // BSTONE_MEMORY_BINARY_READER_INCLUDED
