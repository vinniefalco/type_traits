
//  (C) Copyright John Maddock 2015.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_IS_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED
#define BOOST_TT_IS_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED

#include <boost/type_traits/integral_constant.hpp>
#include <boost/detail/workaround.hpp>

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)

#include <boost/type_traits/detail/yes_no_type.hpp>

namespace boost{

   namespace detail{

      struct is_default_constructible_imp
      {
         template<typename _Tp, typename = decltype(_Tp())>
         static boost::type_traits::yes_type test(int);

         template<typename>
         static boost::type_traits::no_type test(...);
      };

   }

   template <class T> struct is_default_constructible : public integral_constant<bool, sizeof(detail::is_default_constructible_imp::test<T>(0)) == sizeof(boost::type_traits::yes_type)>{};
   template <class T, std::size_t N> struct is_default_constructible<T[N]> : public is_default_constructible<T>{};
   template <class T> struct is_default_constructible<T[]> : public is_default_constructible<T>{};
   template <class T> struct is_default_constructible<T&> : public integral_constant<bool, false>{};
   template <class T> struct is_default_constructible<T&&> : public integral_constant<bool, false>{};
   template <> struct is_default_constructible<void> : public integral_constant<bool, false>{};
   template <> struct is_default_constructible<void const> : public integral_constant<bool, false>{};
   template <> struct is_default_constructible<void volatile> : public integral_constant<bool, false>{};
   template <> struct is_default_constructible<void const volatile> : public integral_constant<bool, false>{};

#else

#include <boost/type_traits/has_trivial_constructor.hpp>

namespace boost{

   // We don't know how to implement this:
   template <class T> struct is_default_constructible : public has_trivial_constructor<T>{};
   template <> struct is_default_constructible<void> : public integral_constant<bool, false>{};
   template <> struct is_default_constructible<void const> : public integral_constant<bool, false>{};
   template <> struct is_default_constructible<void volatile> : public integral_constant<bool, false>{};
   template <> struct is_default_constructible<void const volatile> : public integral_constant<bool, false>{};

#endif

} // namespace boost

#endif // BOOST_TT_IS_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED