// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright © 2014-2022 Allan Leal
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

// Catch includes
#include <catch2/catch.hpp>

// Reaktoro includes
#include <Reaktoro/Models/ActivityModels/Support/CubicEOS.hpp>
using namespace Reaktoro;

TEST_CASE("Testing CubicEOS::Equation class", "[CubicEOS]")
{
    //=============================================
    // FLUID MIXTURE (CO2, H2O, CH4)
    //=============================================
    WHEN("The gases are CO2, H2O, CH4")
    {
        CubicEOS::EquationSpecs eqspecs;
        eqspecs.eqmodel = CubicEOS::EquationModelPengRobinson();
        eqspecs.substances = {
            CubicEOS::Substance{"CO2", 304.20,  73.83e5, 0.2240},
            CubicEOS::Substance{"H2O", 647.10, 220.55e5, 0.3450},
            CubicEOS::Substance{"CH4", 190.60,  45.99e5, 0.0120},
        };

        CubicEOS::Equation equation(eqspecs);
        CubicEOS::Props props;

        ArrayXr x = {{0.90, 0.08, 0.02}};

        WHEN("Conditions correspond to gas state")
        {
            const auto T = 25.0 + 273.15; // 25 °C
            const auto P = 1.0 * 1e5;     // 1 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(0.02464) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.994555) ); // CO2
            CHECK( exp(props.ln_phi[1]) == Approx(0.986592) ); // H2O
            CHECK( exp(props.ln_phi[2]) == Approx(0.998501) ); // CH4

            CHECK( props.som == StateOfMatter::Gas );
        }

        WHEN("Conditions correspond to liquid state")
        {
            const auto T = 10.0 + 273.15; // 10 °C
            const auto P = 100.0 * 1e5;   // 100 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(4.21022e-05) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.375122) );   // CO2
            CHECK( exp(props.ln_phi[1]) == Approx(0.00662715) ); // H2O
            CHECK( exp(props.ln_phi[2]) == Approx(2.21312) );    // CH4

            CHECK( props.som == StateOfMatter::Liquid );
        }

        WHEN("Conditions correspond to supercritical state")
        {
            const auto T = 60.0 + 273.15; // 60 °C
            const auto P = 100.0 * 1e5;   // 100 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(9.33293e-05) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.676616) ); // CO2
            CHECK( exp(props.ln_phi[1]) == Approx(0.137854) ); // H2O
            CHECK( exp(props.ln_phi[2]) == Approx(1.34433) );  // CH4

            CHECK( props.som == StateOfMatter::Supercritical );
        }
    }

    //=============================================
    // FLUID MIXTURE (CO2, H2O)
    //=============================================
    WHEN("The gases are CO2 and H2O")
    {
        CubicEOS::EquationSpecs eqspecs;
        eqspecs.eqmodel = CubicEOS::EquationModelPengRobinson();
        eqspecs.substances = {
            CubicEOS::Substance{"CO2", 304.20,  73.83e5, 0.2240},
            CubicEOS::Substance{"H2O", 647.10, 220.55e5, 0.3450},
        };

        CubicEOS::Equation equation(eqspecs);
        CubicEOS::Props props;

        ArrayXr x = {{0.9, 0.1}};

        WHEN("Conditions correspond to gas state")
        {
            const auto T = 25.0 + 273.15; // 25 °C
            const auto P = 1.0 * 1e5;     // 1 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(0.024634) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.994566) ); // CO2
            CHECK( exp(props.ln_phi[1]) == Approx(0.986475) ); // H2O

            CHECK( props.som == StateOfMatter::Gas );
        }

        WHEN("Conditions correspond to liquid state")
        {
            const auto T = 10.0 + 273.15; // 10 °C
            const auto P = 100.0 * 1e5;   // 100 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(4.04694e-05) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.382635) );   // CO2
            CHECK( exp(props.ln_phi[1]) == Approx(0.00536954) ); // H2O

            CHECK( props.som == StateOfMatter::Liquid );
        }

        WHEN("Conditions correspond to supercritical state")
        {
            const auto T = 60.0 + 273.15; // 60 °C
            const auto P = 100.0 * 1e5;   // 100 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(6.92881e-05) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.707373) );  // CO2
            CHECK( exp(props.ln_phi[1]) == Approx(0.0855991) ); // H2O

            CHECK( props.som == StateOfMatter::Supercritical );
        }
    }

    //=============================================
    // FLUID MIXTURE (CO2)
    //=============================================
    WHEN("There is only CO2")
    {
        CubicEOS::EquationSpecs eqspecs;
        eqspecs.eqmodel = CubicEOS::EquationModelPengRobinson();
        eqspecs.substances = {
            CubicEOS::Substance{"CO2", 304.20,  73.83e5, 0.2240}
        };

        CubicEOS::Equation equation(eqspecs);
        CubicEOS::Props props;

        ArrayXr x = {{1.0}};

        WHEN("Conditions correspond to gas state")
        {
            const auto T = 25.0 + 273.15; // 25 °C
            const auto P = 1.0 * 1e5;     // 1 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(0.0246538) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.994544) ); // CO2

            CHECK( props.som == StateOfMatter::Gas );
        }

        WHEN("Conditions correspond to liquid state")
        {
            const auto T = 10.0 + 273.15; // 10 °C
            const auto P = 100.0 * 1e5;   // 100 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(4.80345e-05) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.36694) ); // CO2

            CHECK( props.som == StateOfMatter::Liquid );
        }

        WHEN("Conditions correspond to supercritical state")
        {
            const auto T = 60.0 + 273.15; // 60 °C
            const auto P = 100.0 * 1e5;   // 100 bar

            equation.compute(props, T, P, x);

            CHECK( props.V == Approx(0.000150429) );

            CHECK( exp(props.ln_phi[0]) == Approx(0.657945) ); // CO2

            CHECK( props.som == StateOfMatter::Supercritical );
        }
    }
}

// Temperatures (in °C) from Table 6 of Duan et al (1992)
const Vec<double> temperatures = { 0, 100, 200, 300, 400, 500, 600, 800, 1000, 1200 };

// Pressures (in bar) from Table 6 of Duan et al (1992)
const Vec<double> pressures = { 1, 20, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000 };

// Fugacity coefficients of CH4 from Table 4 of Duan et al (1992)
const Vec<Vec<double>> phiCH4 =
{
    { 0.9977, 0.9994, 0.9999, 1.0001, 1.0002, 1.0003, 1.0003, 1.0003, 1.0002, 1.0002 },
    { 0.9553, 0.9873, 0.9984, 1.0027, 1.0044, 1.0051, 1.0053, 1.0051, 1.0046, 1.0042 },
    { 0.8915, 0.9697, 0.9967, 1.0071, 1.0113, 1.0129, 1.0133, 1.0128, 1.0117, 1.0106 },
    { 0.7968, 0.9442, 0.9959, 1.0158, 1.0237, 1.0266, 1.0272, 1.0259, 1.0237, 1.0215 },
    { 0.6725, 0.9099, 1.0017, 1.0376, 1.0516, 1.0563, 1.0568, 1.0534, 1.0484, 1.0437 },
    { 0.6223, 0.8991, 1.0179, 1.0655, 1.0835, 1.0266, 1.0887, 1.0823, 1.0743, 1.0668 },
    { 0.6124, 0.9086, 1.0443, 1.0994, 1.1196, 1.1246, 1.1229, 1.1128, 1.1012, 1.0907 },
    { 0.6263, 0.9345, 1.0802, 1.1393, 1.1597, 1.1632, 1.1594, 1.1448, 1.1292, 1.1153 },
    { 0.6565, 0.9737, 1.1249, 1.1851, 1.2040, 1.2050, 1.1983, 1.1783, 1.1582, 1.1408 },
    { 0.7000, 1.0247, 1.1779, 1.2366, 1.2525, 1.2498, 1.2397, 1.2134, 1.1884, 1.1671 },
    { 0.7556, 1.0865, 1.2388, 1.2939, 1.3051, 1.2979, 1.2834, 1.2501, 1.2196, 1.1942 },
    { 0.8229, 1.1588, 1.3076, 1.3569, 1.3620, 1.3491, 1.3297, 1.2884, 1.2520, 1.2221 },
    { 0.9024, 1.2417, 1.3843, 1.4256, 1.4232, 1.4036, 1.3785, 1.3283, 1.2856, 1.2509 },
    { 1.1014, 1.4404, 1.5621, 1.5810, 1.5588, 1.5228, 1.4841, 1.4134, 1.3563, 1.3111 },
    { 1.3628, 1.6874, 1.7746, 1.7615, 1.7130, 1.6560, 1.6007, 1.5056, 1.4319, 1.3749 },
    { 1.7015, 1.9900, 2.0256, 1.9691, 1.8871, 1.8043, 1.7289, 1.6053, 1.5126, 1.4424 },
    { 2.1374, 2.3578, 2.3197, 2.2066, 2.0826, 1.9686, 1.8694, 1.7128, 1.5988, 1.5138 },
    { 2.6964, 2.8027, 2.6630, 2.4770, 2.3015, 2.1580, 2.0230, 1.8286, 1.6905, 1.5892 },
    { 3.4116, 3.3391, 3.0623, 2.7842, 2.5458, 2.3501, 2.1907, 1.9530, 1.7881, 1.6689 },
    { 4.3252, 3.9846, 3.5258, 3.1324, 2.8182, 2.5702, 2.3734, 2.0867, 1.8919, 1.7529 },
    { 5.4910, 4.7603, 4.0629, 3.5263, 3.1211, 2.8120, 2.5722, 2.2301, 2.0022, 1.8415 },
    { 6.9773, 5.6912, 4.6845, 3.9715, 3.4579, 3.0775, 2.7882, 2.3838, 2.1192, 1.9349 },
    { 8.8705, 6.8073, 5.4030, 4.4741, 3.8317, 3.3685, 3.0229, 2.5485, 2.2432, 2.0331 },
    { 11.280, 8.1444, 6.2330, 5.0409, 4.2463, 3.6874, 3.2776, 2.7247, 2.3748, 2.1366 },
    { 14.345, 9.7448, 7.1910, 5.6798, 4.7059, 4.0366, 3.5538, 2.9132, 2.5142, 2.2454 },
    { 18.241, 11.659, 8.2958, 6.3993, 5.2150, 4.4186, 3.8531, 3.1147, 2.6618, 2.3599 },
    { 23.189, 13.948, 9.5692, 7.2091, 5.7786, 4.8364, 4.1774, 3.3300, 2.8180, 2.4802 },
    { 29.469, 16.682, 11.036, 8.1202, 6.4022, 5.2930, 4.5286, 3.5601, 2.9834, 2.6067 },
    { 37.439, 19.946, 12.725, 9.1444, 7.0919, 5.7919, 4.9086, 3.8057, 3.1583, 2.7395 },
    { 47.529, 23.840, 14.668, 10.296, 7.8542, 6.3367, 5.3198, 4.0678, 3.3432, 2.8790 },
    { 60.314, 28.484, 16.902, 11.588, 8.6965, 6.9314, 5.7644, 4.3476, 3.5388, 3.0255 },
    { 76.495, 34.019, 19.471, 13.040, 9.6267, 7.5803, 6.2450, 14.646, 3.7454, 3.1793 },
    { 96.960, 40.612, 22.422, 14.669, 10.654, 8.2881, 6.7646, 4.9642, 3.9638, 3.3407 },
    { 174.91, 63.111, 31.854, 19.660, 13.710, 10.349, 8.2530, 5.8545, 4.5648, 3.7796 },
    { 314.24, 97.779, 45.144, 26.295, 17.611, 12.904, 10.055, 6.8976, 5.2532, 4.2740 },
    { 562.257, 151.024, 63.818, 35.094, 22.579, 16.062, 12.233, 8.1180, 6.0410, 4.8300 },
    { 1001.891, 232.539, 89.986, 46.736, 28.895, 19.960, 14.862, 9.5430, 6.9400, 5.4550 },
    { 1778.045, 356.953, 126.566, 62.104, 36.909, 24.763, 18.030, 11.207, 7.9660, 6.1570 },
    { 3142.950, 546.276, 177.574, 82.352, 47.056, 30.672, 21.841, 13.145, 9.1370, 6.9440 },
    { 5534.102, 833.543, 248.535, 108.974, 59.885, 37.930, 26.420, 15.402, 10.470, 7.8270 },
    { 9707.747, 1268.214, 347.028, 143.908, 76.076, 46.831, 31.915, 18.025, 11.986, 8.8150 },
    { 16966.79, 1924.157, 483.437, 189.664, 96.476, 57.732, 38.499, 21.073, 13.711, 9.9210 },
    { 29584.79, 2911.439, 671.958, 249.488, 122.138, 71.064, 46.379, 24.609, 15.670, 11.158 },
};

// Fugacity coefficients of CO2 from Table 5 of Duan et al (1992)
const Vec<Vec<double>> phiCO2 =
{
    { 0.9931, 0.9976, 0.9991, 0.9997, 1.0000, 1.0001, 1.0002, 1.0002, 1.0002, 1.0002 },
    { 0.8648, 0.9537, 0.9825, 0.9941, 0.9993, 1.0018, 1.0031, 1.0040, 1.0041, 1.0039 },
    { 0.5695, 0.8870, 0.9574, 0.9857, 0.9985, 1.0047, 1.0078, 1.0100, 1.0102, 1.0098 },
    { 0.3152, 0.7839, 0.9184, 0.9731, 0.9980, 1.0101, 1.0162, 1.0204, 1.0207, 1.0198 },
    { 0.1914, 0.6186, 0.8530, 0.9535, 1.0003, 1.0232, 1.0345, 1.0422, 1.0424, 1.0402 },
    { 0.1538, 0.5264, 0.8062, 0.9420, 1.0071, 1.0101, 1.0550, 1.0654, 1.0650, 1.0615 },
    { 0.1383, 0.4817, 0.7780, 0.9386, 1.0186, 1.0583, 1.0778, 1.0900, 1.0887, 1.0835 },
    { 0.1321, 0.4612, 0.7656, 0.9432, 1.0348, 1.0807, 1.1029, 1.1161, 1.1134, 1.1062 },
    { 0.1310, 0.4549, 0.7654, 0.9553, 1.0557, 1.1062, 1.1305, 1.1437, 1.1391, 1.1298 },
    { 0.1332, 0.4578, 0.7748, 0.9741, 1.0811, 1.1351, 1.1606, 1.1728, 1.1660, 1.1541 },
    { 0.1380, 0.4676, 0.7919, 0.9990, 1.1111, 1.1673, 1.1932, 1.2037, 1.1939, 1.1793 },
    { 0.1449, 0.4828, 0.8156, 1.0294, 1.1453, 1.2028, 1.2283, 1.2361, 1.2231, 1.2053 },
    { 0.1537, 0.5029, 0.8451, 1.0651, 1.1838, 1.2416, 1.2661, 1.2704, 1.2534, 1.2323 },
    { 0.1770, 0.5560, 0.9201, 1.1512, 1.2729, 1.3292, 1.3498, 1.3442, 1.3179, 1.2889 },
    { 0.2085, 0.6259, 1.0153, 1.2564, 1.3783, 1.4300, 1.4443, 1.4253, 1.3876, 1.3493 },
    { 0.2494, 0.7136, 1.1312, 1.3808, 1.5003, 1.5447, 1.5501, 1.5143, 1.4628, 1.4138 },
    { 0.3018, 0.8210, 1.2691, 1.5256, 1.6395, 1.6736, 1.6677, 1.6113, 1.5437, 1.4825 },
    { 0.3683, 0.9511, 1.4312, 1.6922, 1.7972, 1.8177, 1.7977, 1.7167, 1.6306, 1.5556 },
    { 0.4525, 1.1076, 1.6206, 1.8828, 1.9746, 1.9779, 1.9408, 1.8311, 1.7238, 1.6332 },
    { 0.5587, 1.2951, 1.8406, 2.0997, 2.1737, 2.1554, 2.0979, 1.9548, 1.8235, 1.7157 },
    { 0.6926, 1.5192, 2.0956, 2.3460, 2.3962, 2.3517, 2.2700, 2.0885, 1.9301, 1.8032 },
    { 0.8615, 1.7865, 2.3904, 2.6249, 2.6446, 2.5683, 2.4581, 2.2326, 2.0439, 1.8958 },
    { 1.0743, 2.1051, 2.7308, 2.9404, 2.9214, 2.8069, 2.6636, 2.3878, 2.1653, 1.9939 },
    { 1.3427, 2.4847, 3.1235, 3.2968, 3.2294, 3.0694, 2.8876, 2.5548, 2.2947, 2.0977 },
    { 1.6810, 2.9366, 3.5760, 3.6990, 3.5719, 3.3580, 3.1316, 2.7343, 2.4324, 2.2074 },
    { 2.1077, 3.4744, 4.0973, 4.1525, 3.9523, 3.6750, 3.3973, 2.9272, 2.5790, 2.3232 },
    { 2.6458, 4.1143, 4.6973, 4.6636, 4.3746, 4.0230, 3.6864, 3.1343, 2.7349, 2.4456 },
    { 3.3245, 4.8754, 5.3878, 5.2393, 4.8431, 4.4047, 4.0007, 3.3565, 2.9007, 2.5748 },
    { 4.1807, 5.7805, 6.1820, 5.8874, 5.3627, 4.8232, 4.3422, 3.5948, 3.0768, 2.7111 },
    { 5.2609, 6.8567, 7.0951, 6.6167, 5.9386, 5.2819, 4.7132, 3.8503, 3.2638, 2.8549 },
    { 6.6237, 8.1361, 8.1448, 7.4372, 6.5768, 5.7843, 5.1161, 4.1241, 3.4624, 3.0064 },
    { 8.3431, 9.6567, 9.3509, 8.3598, 7.2835, 6.3346, 5.5533, 4.4174, 3.6731, 3.1662 },
    { 10.512, 11.464, 10.7366, 9.3969, 8.0661, 6.9369, 6.0277, 4.7315, 3.8967, 3.3345 },
    { 18.753, 17.611, 15.168, 12.586, 10.4072, 8.7027, 7.3967, 5.6170, 4.5169, 3.7956 },
    { 33.476, 27.059, 21.422, 16.847, 13.419, 10.9107, 9.0710, 6.6654, 5.2344, 4.3200 },
    { 59.764, 41.561, 30.233, 22.532, 17.286, 13.667, 11.116, 7.9050, 6.0630, 4.9160 },
    { 106.650, 63.791, 42.631, 30.105, 22.245, 17.103, 13.609, 9.3680, 7.0200, 5.5920 },
    { 190.180, 97.823, 60.047, 40.175, 28.593, 21.378, 16.644, 11.094, 8.1230, 6.3580 },
    { 338.799, 149.846, 84.477, 53.547, 36.708, 26.693, 20.336, 13.127, 9.3940, 7.2260 },
    { 602.863, 229.258, 118.695, 71.279, 47.067, 33.289, 24.820, 15.518, 10.856, 8.2080 },
    { 1071.365, 350.305, 166.553, 94.756, 60.272, 41.466, 30.259, 18.330, 12.537, 9.3180 },
    { 1901.339, 534.546, 233.394, 125.798, 77.084, 51.590, 36.850, 21.631, 14.467, 10.572 },
    { 3369.441, 814.565, 326.616, 166.788, 98.460, 64.109, 44.828, 25.504, 16.683, 11.989 },
};

// Fugacity coefficients of H2O from Table 6 of Duan et al (1992)
const Vec<Vec<double>> phiH2O =
{
    { 0.1831, 0.9890, 0.9950, 0.9974, 0.9986, 0.9991, 0.9995, 0.9998, 0.9999, 1.0000 },
    { 0.0095, 0.0875, 0.7615, 0.9491, 0.9713, 0.9830, 0.9897, 0.9962, 0.9989, 1.0002 },
    { 0.0033, 0.0356, 0.3095, 0.8737, 0.9290, 0.9579, 0.9743, 0.9905, 0.9973, 1.0005 },
    { 0.0017, 0.0184, 0.1589, 0.6628, 0.8598, 0.9168, 0.9492, 0.9812, 0.9947, 1.0011 },
    { 0.0009, 0.0098, 0.0837, 0.3490, 0.7244, 0.8378, 0.9008, 0.9631, 0.9898, 1.0023 },
    { 0.0007, 0.0069, 0.0588, 0.2448, 0.5808, 0.9168, 0.8549, 0.9460, 0.9851, 1.0036 },
    { 0.0005, 0.0055, 0.0464, 0.1930, 0.4672, 0.6935, 0.8118, 0.9297, 0.9808, 1.0051 },
    { 0.0005, 0.0047, 0.0391, 0.1621, 0.3962, 0.6311, 0.7719, 0.9143, 0.9769, 1.0067 },
    { 0.0004, 0.0041, 0.0343, 0.1418, 0.3486, 0.5781, 0.7353, 0.8998, 0.9732, 1.0085 },
    { 0.0004, 0.0038, 0.0309, 0.1275, 0.3146, 0.5349, 0.7025, 0.8863, 0.9699, 1.0105 },
    { 0.0004, 0.0035, 0.0284, 0.1169, 0.2892, 0.5000, 0.6734, 0.8738, 0.9670, 1.0125 },
    { 0.0004, 0.0033, 0.0266, 0.1089, 0.2698, 0.4717, 0.6480, 0.8623, 0.9644, 1.0148 },
    { 0.0003, 0.0031, 0.0251, 0.1026, 0.2545, 0.4487, 0.6258, 0.8517, 0.9622, 1.0172 },
    { 0.0003, 0.0029, 0.0231, 0.0937, 0.2324, 0.4141, 0.5902, 0.8334, 0.9589, 1.0225 },
    { 0.0003, 0.0028, 0.0219, 0.0878, 0.2175, 0.3901, 0.5637, 0.8188, 0.9569, 1.0284 },
    { 0.0003, 0.0028, 0.0211, 0.0839, 0.2074, 0.3732, 0.5442, 0.8075, 0.9564, 1.0350 },
    { 0.0003, 0.0027, 0.0206, 0.0814, 0.2005, 0.3614, 0.5302, 0.7993, 0.9574, 1.0424 },
    { 0.0004, 0.0028, 0.0204, 0.0799, 0.1959, 0.3533, 0.5203, 0.7939, 0.9596, 1.0504 },
    { 0.0004, 0.0028, 0.0204, 0.0790, 0.1931, 0.3480, 0.5138, 0.7909, 0.9633, 1.0592 },
    { 0.0004, 0.0029, 0.0205, 0.0788, 0.1916, 0.3449, 0.5100, 0.7902, 0.9682, 1.0687 },
    { 0.0004, 0.0030, 0.0208, 0.0791, 0.1913, 0.3437, 0.5084, 0.7914, 0.9744, 1.0790 },
    { 0.0005, 0.0031, 0.0212, 0.0797, 0.1919, 0.3440, 0.5087, 0.7944, 0.9818, 1.0900 },
    { 0.0005, 0.0032, 0.0217, 0.0808, 0.1933, 0.3455, 0.5107, 0.7991, 0.9904, 1.1018 },
    { 0.0005, 0.0034, 0.0223, 0.0821, 0.1954, 0.3483, 0.5142, 0.8052, 1.0000, 1.1144 },
    { 0.0006, 0.0035, 0.0230, 0.0838, 0.1981, 0.3520, 0.5190, 0.8128, 1.0108, 1.1277 },
    { 0.0006, 0.0037, 0.0237, 0.0857, 0.2014, 0.3566, 0.5249, 0.8216, 1.0226, 1.1417 },
    { 0.0007, 0.0039, 0.0246, 0.0879, 0.2053, 0.3621, 0.5319, 0.8317, 1.0354, 1.1566 },
    { 0.0008, 0.0041, 0.0255, 0.0904, 0.2096, 0.3684, 0.5400, 0.8428, 1.0492, 1.1721 },
    { 0.0008, 0.0044, 0.0266, 0.0931, 0.2145, 0.3754, 0.5490, 0.8551, 1.0639, 1.1884 },
    { 0.0009, 0.0047, 0.0277, 0.0960, 0.2198, 0.3832, 0.5589, 0.8684, 1.0796, 1.2055 },
    { 0.0010, 0.0050, 0.0290, 0.0992, 0.2256, 0.3916, 0.5697, 0.8828, 1.0961, 1.2233 },
    { 0.0011, 0.0053, 0.0303, 0.1027, 0.2319, 0.4008, 0.5813, 0.8981, 1.1136, 1.2418 },
    { 0.0012, 0.0056, 0.0317, 0.1064, 0.2387, 0.4106, 0.5938, 0.9144, 1.1320, 1.2611 },
    { 0.0016, 0.0066, 0.0358, 0.1168, 0.2576, 0.4380, 0.6286, 0.9592, 1.1817, 1.3124 },
    { 0.0020, 0.0079, 0.0407, 0.1290, 0.2795, 0.4697, 0.6685, 1.0098, 1.2369, 1.3684 },
    { 0.0026, 0.0094, 0.0464, 0.1432, 0.3046, 0.5057, 0.7136, 1.0662, 1.2974, 1.4290 },
    { 0.0034, 0.0113, 0.0531, 0.1595, 0.3333, 0.5463, 0.7641, 1.1286, 1.3635, 1.4943 },
    { 0.0044, 0.0135, 0.0610, 0.1783, 0.3656, 0.5919, 0.8203, 1.1969, 1.4351, 1.5645 },
    { 0.0057, 0.0163, 0.0703, 0.1997, 0.4022, 0.6427, 0.8824, 1.2716, 1.5125, 1.6396 },
    { 0.0074, 0.0197, 0.0812, 0.2243, 0.4433, 0.6992, 0.9509, 1.3528, 1.5959, 1.7199 },
    { 0.0097, 0.0238, 0.0939, 0.2523, 0.4894, 0.7619, 1.0262, 1.4410, 1.6855, 1.8054 },
    { 0.0126, 0.0288, 0.1088, 0.2842, 0.5411, 0.8313, 1.1089, 1.5366, 1.7817, 1.8964 },
    { 0.0165, 0.0350, 0.1262, 0.3206, 0.5991, 0.9081, 1.1995, 1.6399, 1.8846, 1.9932 },
};
