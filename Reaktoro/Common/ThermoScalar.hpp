// Reaktoro is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// C++ includes
#include <functional>

// Reaktoro includes
#include <Reaktoro/Common/TraitsUtils.hpp>

namespace Reaktoro {

// Forward declarations
class ThermoVectorRow;
class ThermoVectorConstRow;

/// Describe a thermodynamic property value and its partial derivatives w.r.t. temperature and pressure
class ThermoScalar
{
public:
    /// Construct a default ThermoScalar instance
    ThermoScalar();

    /// Construct a custom ThermoScalar instance with given value only.
    /// @param val The value of the thermodynamic property
    explicit ThermoScalar(double val);

    /// Construct a custom ThermoScalar instance with given value and derivatives.
    /// @param val The value of the thermodynamic property
    /// @param ddt The partial temperature derivative of the thermodynamic property
    /// @param ddp The partial pressure derivative of the thermodynamic property
    ThermoScalar(double val, double ddt, double ddp);

    /// Assign a row of a ThermoVector instance to this ThermoScalar instance
    auto operator=(const ThermoVectorRow& row) -> ThermoScalar&;

    /// Assign a row of a ThermoVector instance to this ThermoScalar instance
    auto operator=(const ThermoVectorConstRow& row) -> ThermoScalar&;

    /// Assign-addition of a ThermoScalar instance
    auto operator+=(const ThermoScalar& other) -> ThermoScalar&;

    /// Assign-subtraction of a ThermoScalar instance
    auto operator-=(const ThermoScalar& other) -> ThermoScalar&;

    /// Assign-multiplication of a ThermoScalar instance
    auto operator*=(const ThermoScalar& other) -> ThermoScalar&;

    /// Assign-division of a ThermoScalar instance
    auto operator/=(const ThermoScalar& other) -> ThermoScalar&;

    /// Assign a scalar to this ThermoScalar instance
    template<typename Type, EnableIfScalar<Type>...>
    auto operator=(Type scalar) -> ThermoScalar&;

    /// Assign-addition of a scalar
    template<typename Type, EnableIfScalar<Type>...>
    auto operator+=(Type scalar) -> ThermoScalar&;

    /// Assign-subtraction of a scalar
    template<typename Type, EnableIfScalar<Type>...>
    auto operator-=(Type scalar) -> ThermoScalar&;

    /// Assign-multiplication of a ThermoScalar instance
    template<typename Type, EnableIfScalar<Type>...>
    auto operator*=(Type scalar) -> ThermoScalar&;

    /// Assign-division of a ThermoScalar instance
    template<typename Type, EnableIfScalar<Type>...>
    auto operator/=(Type scalar) -> ThermoScalar&;

    /// Convert this ThermoScalar instance into double
    operator double() { return val; }

    /// Convert this ThermoScalar instance into double
    operator double() const { return val; }

    /// The value of the thermodynamic property
    double val = 0.0;

    /// The partial temperature derivative of the thermodynamic property
    double ddt = 0.0;

    /// The partial pressure derivative of the thermodynamic property
    double ddp = 0.0;
};

/// A type that describes temperature in units of K
class Temperature : public ThermoScalar
{
public:
    /// Construct a default Temperature instance
    Temperature() : Temperature(0.0) {}

    /// Construct a Temperature instance with given value
    Temperature(double val) : ThermoScalar(val, 1.0, 0.0) {}
};

/// A type that describes pressure in units of Pa
class Pressure : public ThermoScalar
{
public:
    /// Construct a default Pressure instance
    Pressure() : Pressure(0.0) {}

    /// Construct a Pressure instance with given value
    Pressure(double val) : ThermoScalar(val, 0.0, 1.0) {}
};

/// A type used to define the function signature for the calculation of a thermodynamic property.
/// @see ThermoScalar, ThermoVector, ThermoVectorFunction
using ThermoScalarFunction = std::function<ThermoScalar(double, double)>;

/// Output a ThermoScalar instance
auto operator<<(std::ostream& out, const ThermoScalar& scalar) -> std::ostream&;

/// Unary addition operator for a ThermoScalar instance
auto operator+(const ThermoScalar& l) -> ThermoScalar;

/// Unary subtraction operator for a ThermoScalar instance
auto operator-(const ThermoScalar& l) -> ThermoScalar;

/// Subtract two ThermoScalar instances
auto operator-(const ThermoScalar& l, const ThermoScalar& r) -> ThermoScalar;

/// Add two ThermoScalar instances
auto operator+(const ThermoScalar& l, const ThermoScalar& r) -> ThermoScalar;

/// Multiply two ThermoScalar instances
auto operator*(const ThermoScalar& l, const ThermoScalar& r) -> ThermoScalar;

/// Divide a ThermoScalar instance by another
auto operator/(const ThermoScalar& l, const ThermoScalar& r) -> ThermoScalar;

/// Return the square root of a ThermoScalar instance
auto sqrt(const ThermoScalar& l) -> ThermoScalar;

/// Return the power of a ThermoScalar instance
auto pow(const ThermoScalar& l, const ThermoScalar& power) -> ThermoScalar;

/// Return the natural exponential of a ThermoScalar instance
auto exp(const ThermoScalar& l) -> ThermoScalar;

/// Return the natural log of a ThermoScalar instance
auto log(const ThermoScalar& l) -> ThermoScalar;

/// Return the log10 of a ThermoScalar instance
auto log10(const ThermoScalar& l) -> ThermoScalar;

/// Return true if a ThermoScalar instance is less than another
auto operator<(const ThermoScalar& l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is less or equal than another
auto operator<=(const ThermoScalar& l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is greater than another
auto operator>(const ThermoScalar& l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is greater or equal than another
auto operator>=(const ThermoScalar& l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is equal to another
auto operator==(const ThermoScalar& l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is not equal to another
auto operator!=(const ThermoScalar& l, const ThermoScalar& r) -> bool;

/// Left-add a ThermoScalar instance by a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator+(Type scalar, const ThermoScalar& r) -> ThermoScalar;

/// Right-add a ThermoScalar instance by a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator+(const ThermoScalar& l, Type scalar) -> ThermoScalar;

/// Right-subtract a ThermoScalar instance by a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator-(const ThermoScalar& l, Type scalar) -> ThermoScalar;

/// Left-subtract a ThermoScalar instance by a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator-(Type scalar, const ThermoScalar& r) -> ThermoScalar;

/// Left-multiply a ThermoScalar instance by a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator*(Type scalar, const ThermoScalar& r) -> ThermoScalar;

/// Right-multiply a ThermoScalar instance by a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator*(const ThermoScalar& l, Type scalar) -> ThermoScalar;

/// Left-divide a ThermoScalar instance by a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator/(Type scalar, const ThermoScalar& r) -> ThermoScalar;

/// Right-divide a ThermoScalar instance by a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator/(const ThermoScalar& l, Type scalar) -> ThermoScalar;

/// Return the power of a ThermoScalar instance
template<typename Type, EnableIfScalar<Type>...>
auto pow(const ThermoScalar& l, Type power) -> ThermoScalar;

/// Return true if a scalar is less than a ThermoScalar instance
template<typename Type, EnableIfScalar<Type>...>
auto operator<(Type l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is less than a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator<(const ThermoScalar& l, Type r) -> bool;
/// Return true if a scalar is less or equal than a ThermoScalar instance
template<typename Type, EnableIfScalar<Type>...>
auto operator<=(Type l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is less or equal than a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator<=(const ThermoScalar& l, Type r) -> bool;

/// Return true if a scalar is greater than a ThermoScalar instance
template<typename Type, EnableIfScalar<Type>...>
auto operator>(Type l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar is greater than a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator>(const ThermoScalar& l, Type r) -> bool;

/// Return true if a scalar is greater or equal than a ThermoScalar instance
template<typename Type, EnableIfScalar<Type>...>
auto operator>=(Type l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is greater or equal than a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator>=(const ThermoScalar& l, Type r) -> bool;

/// Return true if a scalar is equal to a ThermoScalar instance
template<typename Type, EnableIfScalar<Type>...>
auto operator==(Type l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is equal to a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator==(const ThermoScalar& l, Type r) -> bool;

/// Return true if a scalar is not equal to a ThermoScalar instance
template<typename Type, EnableIfScalar<Type>...>
auto operator!=(Type l, const ThermoScalar& r) -> bool;

/// Return true if a ThermoScalar instance is not equal to a scalar
template<typename Type, EnableIfScalar<Type>...>
auto operator!=(const ThermoScalar& l, Type r) -> bool;

} // namespace Reaktoro

#include "ThermoScalar.hxx"
