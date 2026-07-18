#include <iostream>

#include "autotests_float2.h"
#include "autotests_float3.h"
#include "autotests_float4.h"

#include "autotests_float2x2.h"
#include "autotests_float3x3.h"
#include "autotests_float4x4.h"

#include "autotests_half.h"
#include "autotests_half2.h"
#include "autotests_half3.h"
#include "autotests_half4.h"

#include "autotests_quaternion.h"

int main()
{
    AfterMathTests::RunFloat2Tests();
    AfterMathTests::RunFloat3Tests();
    AfterMathTests::RunFloat4Tests();

    AfterMathTests::RunFloat2x2Tests();
    AfterMathTests::RunFloat3x3Tests();
    AfterMathTests::RunFloat4x4Tests();
    
    AfterMathTests::RunHalfTests();
    AfterMathTests::RunHalf2Tests();
    AfterMathTests::RunHalf3Tests();
    AfterMathTests::RunHalf4Tests();

    AfterMathTests::RunQuaternionTests();

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}