#pragma once

namespace urus
{
	/**
	 * Lazy-evaluated thread-safe singleton
	 * 
	 * Usage as curiously recurring template pattern (CRTP):
	 * 
	 class Foo: public Singleton<Foo> // now Foo is a Singleton
	 {
	 friend class Singleton<Foo>;
	 ~Foo(){}
	 Foo(){};
	 public:
	// methods
	};
	 *
	 * 
	 */
	template <typename T>
		class Singleton
		{
			//friend T;

			public:
				static T& sharedInstance() 
				{
					static T instance; 

					return instance;
				}
				Singleton(const Singleton&) = delete;
				Singleton& operator=(const Singleton&) = delete;

				virtual ~Singleton() = default;

			protected:
				Singleton() = default;
		}; // class Singleton
} // namespace urus
