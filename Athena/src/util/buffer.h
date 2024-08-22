#pragma once
#ifndef BUFFER
#define BUFFER
#include <vector>
#include <type_traits>

namespace athena
{
    class buffer;
    // Trait to check if T has a member function serialize with the given signature
    template <typename T>
    struct has_serialize_method
    {
    private:
        // Helper template to check if the serialize method exists and has the correct signature
        template <typename U>
        static auto test(int) -> decltype(std::declval<U>().serialize(std::declval<athena::buffer*>(), std::declval<const U&>()), void(), std::true_type{});

        template <typename>
        static std::false_type test(...);

    public:
        using type = decltype(test<T>(0));
        static constexpr bool value = type::value;
    };

	class buffer 
	{
	public:

		void writeData(const char* data, size_t size);
		void setPointerPosition(size_t size);

        const size_t size() const { return m_data.size(); };

        template<typename T>
        typename std::enable_if<std::is_trivially_copyable<T>::value>::type
            writeObject(const T& object) {
            writeData(reinterpret_cast<const char*>(&object), sizeof(T));
        }

        template<typename T>
        typename std::enable_if<!std::is_trivially_copyable<T>::value>::type
            writeObject(const T& object) {
            // Ensure that T has a serialize method
            static_assert(has_serialize_method<T>::value,
                "T must have a serialize function with signature void (athena::buffer*, const T&)");

            // Call the serialize method on the object
            T::serialize(this, object);
        }
        static void serialize(buffer* dstBuffer,const buffer& srcBuffer)
        {
            dstBuffer->writeData((const char*)srcBuffer.m_data.data(), srcBuffer.size());
        }
		operator size_t() const { return m_data.size(); };
	private:
		size_t m_pointerPosition = 0; //this allows for data to be inserted in the middle of the buffer!
		std::vector<uint8_t> m_data; //we use data vector for convenience
	};

}
#endif // !BUFFER
