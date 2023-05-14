# Level 2

## size = 64

| relative |               ns/op |                op/s |    err% |     total | sgemv:N
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |              251.70 |        3,973,031.94 |    0.8% |      0.01 | `cblas`
|    46.5% |              540.88 |        1,848,854.78 |    2.8% |      0.02 | `meatballs`
|     8.9% |            2,818.78 |          354,763.25 |    0.9% |      0.02 | `naive`

| relative |               ns/op |                op/s |    err% |     total | sgemv:T
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |              168.06 |        5,950,377.77 |    0.7% |      0.01 | `cblas`
|    26.7% |              630.30 |        1,586,538.65 |    0.6% |      0.02 | `meatballs`
|     5.8% |            2,920.35 |          342,424.76 |    2.0% |      0.02 | `naive`

| relative |               ns/op |                op/s |    err% |     total | ssymv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |              561.03 |        1,782,443.63 |   10.3% |      0.01 | :wavy_dash: `cblas` (Unstable with ~1,218.5 iters. Increase `minEpochIterations` to e.g. 12185)
|    45.0% |            1,246.07 |          802,522.79 |   21.6% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~336.7 iters. Increase `minEpochIterations` to e.g. 3367)
|    24.3% |            2,308.25 |          433,228.44 |   12.4% |      0.02 | :wavy_dash: `naive` (Unstable with ~469.4 iters. Increase `minEpochIterations` to e.g. 4694)

| relative |               ns/op |                op/s |    err% |     total | ssymv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |              419.90 |        2,381,512.86 |    2.5% |      0.02 | `cblas`
|    46.1% |              910.12 |        1,098,758.21 |    1.7% |      0.02 | `meatballs`
|    13.4% |            3,142.09 |          318,259.78 |    3.6% |      0.02 | `naive`

| relative |               ns/op |                op/s |    err% |     total | strmv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |            1,122.94 |          890,516.67 |    3.1% |      0.02 | `cblas`
|    79.0% |            1,420.91 |          703,772.39 |   17.8% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~678.9 iters. Increase `minEpochIterations` to e.g. 6789)
|    87.2% |            1,287.33 |          776,799.38 |    6.7% |      0.02 | :wavy_dash: `naive` (Unstable with ~748.7 iters. Increase `minEpochIterations` to e.g. 7487)

| relative |               ns/op |                op/s |    err% |     total | strmv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |            1,331.09 |          751,261.41 |    5.5% |      0.01 | :wavy_dash: `cblas` (Unstable with ~844.1 iters. Increase `minEpochIterations` to e.g. 8441)
|   135.4% |              983.28 |        1,017,003.85 |    6.0% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~665.9 iters. Increase `minEpochIterations` to e.g. 6659)
|   113.8% |            1,169.42 |          855,125.48 |    5.8% |      0.01 | :wavy_dash: `naive` (Unstable with ~935.8 iters. Increase `minEpochIterations` to e.g. 9358)

## size = 256

| relative |               ns/op |                op/s |    err% |     total | sgemv:N
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |            4,989.94 |          200,403.37 |    5.2% |      0.01 | :wavy_dash: `cblas` (Unstable with ~217.5 iters. Increase `minEpochIterations` to e.g. 2175)
|    77.4% |            6,443.24 |          155,201.36 |    2.0% |      0.01 | `meatballs`
|     5.8% |           85,623.00 |           11,679.10 |   12.1% |      0.01 | :wavy_dash: `naive` (Unstable with ~9.5 iters. Increase `minEpochIterations` to e.g. 95)

| relative |               ns/op |                op/s |    err% |     total | sgemv:T
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |            4,435.92 |          225,432.39 |    2.6% |      0.01 | `cblas`
|    59.8% |            7,423.00 |          134,716.42 |    7.2% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~86.0 iters. Increase `minEpochIterations` to e.g. 860)
|     6.3% |           70,114.93 |           14,262.30 |    4.8% |      0.01 | `naive`

| relative |               ns/op |                op/s |    err% |     total | ssymv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |            4,360.23 |          229,345.87 |    1.6% |      0.01 | `cblas`
|    42.7% |           10,217.53 |           97,870.97 |   17.5% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~107.3 iters. Increase `minEpochIterations` to e.g. 1073)
|    11.1% |           39,397.03 |           25,382.62 |    1.1% |      0.01 | `naive`

| relative |               ns/op |                op/s |    err% |     total | ssymv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |            4,820.19 |          207,460.83 |   10.7% |      0.01 | :wavy_dash: `cblas` (Unstable with ~131.8 iters. Increase `minEpochIterations` to e.g. 1318)
|    50.8% |            9,479.67 |          105,488.94 |   16.3% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~112.1 iters. Increase `minEpochIterations` to e.g. 1121)
|     8.1% |           59,442.63 |           16,822.94 |    3.2% |      0.01 | `naive`

| relative |               ns/op |                op/s |    err% |     total | strmv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |            8,515.23 |          117,436.61 |    8.9% |      0.01 | :wavy_dash: `cblas` (Unstable with ~97.5 iters. Increase `minEpochIterations` to e.g. 975)
|   155.3% |            5,481.98 |          182,415.98 |    2.4% |      0.01 | `meatballs`
|    28.9% |           29,460.29 |           33,944.00 |    4.8% |      0.01 | `naive`

| relative |               ns/op |                op/s |    err% |     total | strmv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |            8,500.08 |          117,645.95 |    6.8% |      0.01 | :wavy_dash: `cblas` (Unstable with ~123.4 iters. Increase `minEpochIterations` to e.g. 1234)
|   164.3% |            5,174.14 |          193,268.97 |    5.0% |      0.01 | `meatballs`
|    25.9% |           32,804.15 |           30,483.94 |   13.6% |      0.01 | :wavy_dash: `naive` (Unstable with ~29.3 iters. Increase `minEpochIterations` to e.g. 293)

## size = 1024

| relative |               ns/op |                op/s |    err% |     total | sgemv:N
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |          188,735.17 |            5,298.43 |   15.8% |      0.01 | :wavy_dash: `cblas` (Unstable with ~5.5 iters. Increase `minEpochIterations` to e.g. 55)
|    80.5% |          234,452.00 |            4,265.27 |    8.1% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~2.7 iters. Increase `minEpochIterations` to e.g. 27)
|     4.5% |        4,167,039.00 |              239.98 |    8.0% |      0.05 | :wavy_dash: `naive` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)

| relative |               ns/op |                op/s |    err% |     total | sgemv:T
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |          172,187.43 |            5,807.62 |    5.7% |      0.01 | :wavy_dash: `cblas` (Unstable with ~6.1 iters. Increase `minEpochIterations` to e.g. 61)
|    68.0% |          253,152.50 |            3,950.19 |   16.6% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~2.1 iters. Increase `minEpochIterations` to e.g. 21)
|    13.9% |        1,235,911.00 |              809.12 |    5.2% |      0.01 | :wavy_dash: `naive` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)

| relative |               ns/op |                op/s |    err% |     total | ssymv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |           93,263.37 |           10,722.32 |   14.2% |      0.01 | :wavy_dash: `cblas` (Unstable with ~8.1 iters. Increase `minEpochIterations` to e.g. 81)
|    38.5% |          242,068.67 |            4,131.06 |    7.0% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~3.5 iters. Increase `minEpochIterations` to e.g. 35)
|     9.8% |          956,109.00 |            1,045.91 |    9.3% |      0.01 | :wavy_dash: `naive` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)

| relative |               ns/op |                op/s |    err% |     total | ssymv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |          123,944.14 |            8,068.15 |   18.5% |      0.01 | :wavy_dash: `cblas` (Unstable with ~8.0 iters. Increase `minEpochIterations` to e.g. 80)
|    52.8% |          234,677.25 |            4,261.17 |    6.3% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~4.5 iters. Increase `minEpochIterations` to e.g. 45)
|    10.4% |        1,197,311.00 |              835.20 |    5.2% |      0.01 | :wavy_dash: `naive` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)

| relative |               ns/op |                op/s |    err% |     total | strmv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |          117,163.62 |            8,535.07 |   16.6% |      0.01 | :wavy_dash: `cblas` (Unstable with ~7.9 iters. Increase `minEpochIterations` to e.g. 79)
|    96.1% |          121,861.20 |            8,206.06 |   23.7% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~6.4 iters. Increase `minEpochIterations` to e.g. 64)
|    16.4% |          715,607.00 |            1,397.42 |   11.0% |      0.01 | :wavy_dash: `naive` (Unstable with ~1.5 iters. Increase `minEpochIterations` to e.g. 15)

| relative |               ns/op |                op/s |    err% |     total | strmv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |          121,767.89 |            8,212.35 |    8.4% |      0.01 | :wavy_dash: `cblas` (Unstable with ~9.4 iters. Increase `minEpochIterations` to e.g. 94)
|    97.8% |          124,476.25 |            8,033.66 |   10.7% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~6.6 iters. Increase `minEpochIterations` to e.g. 66)
|    16.6% |          735,707.00 |            1,359.24 |   11.2% |      0.02 | :wavy_dash: `naive` (Unstable with ~1.7 iters. Increase `minEpochIterations` to e.g. 17)

## size = 4096

| relative |               ns/op |                op/s |    err% |     total | sgemv:N
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        4,083,938.00 |              244.86 |    1.6% |      0.05 | `cblas`
|    73.7% |        5,541,352.00 |              180.46 |   21.5% |      0.07 | :wavy_dash: `meatballs` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|     2.7% |      149,810,702.00 |                6.68 |    0.6% |      1.65 | `naive`

| relative |               ns/op |                op/s |    err% |     total | sgemv:T
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        4,228,340.00 |              236.50 |   15.1% |      0.05 | :wavy_dash: `cblas` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    93.8% |        4,508,142.00 |              221.82 |    5.7% |      0.05 | :wavy_dash: `meatballs` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    18.0% |       23,555,221.00 |               42.45 |    5.0% |      0.27 | `naive`

| relative |               ns/op |                op/s |    err% |     total | ssymv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        2,699,625.00 |              370.42 |   32.4% |      0.03 | :wavy_dash: `cblas` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    40.6% |        6,654,062.00 |              150.28 |   24.9% |      0.07 | :wavy_dash: `meatballs` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    16.3% |       16,516,054.00 |               60.55 |   14.6% |      0.19 | :wavy_dash: `naive` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)

| relative |               ns/op |                op/s |    err% |     total | ssymv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        2,370,022.00 |              421.94 |    5.7% |      0.03 | :wavy_dash: `cblas` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    31.3% |        7,567,771.00 |              132.14 |   31.7% |      0.08 | :wavy_dash: `meatballs` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    11.6% |       20,344,590.00 |               49.15 |    6.7% |      0.23 | :wavy_dash: `naive` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)

| relative |               ns/op |                op/s |    err% |     total | strmv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        2,394,522.00 |              417.62 |    8.0% |      0.03 | :wavy_dash: `cblas` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    94.0% |        2,546,824.00 |              392.65 |    8.9% |      0.03 | :wavy_dash: `meatballs` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    22.9% |       10,474,998.00 |               95.47 |    2.8% |      0.12 | `naive`

| relative |               ns/op |                op/s |    err% |     total | strmv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        2,507,024.00 |              398.88 |    3.3% |      0.03 | `cblas`
|   100.2% |        2,502,924.00 |              399.53 |    8.0% |      0.03 | :wavy_dash: `meatballs` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    23.7% |       10,557,399.00 |               94.72 |    3.1% |      0.12 | `naive`

## size = 8192

| relative |               ns/op |                op/s |    err% |     total | sgemv:N
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |       15,127,142.00 |               66.11 |    2.3% |      0.17 | `cblas`
|    82.6% |       18,316,571.00 |               54.60 |    2.6% |      0.20 | `meatballs`
|     2.2% |      672,858,259.00 |                1.49 |    0.6% |      7.45 | `naive`

| relative |               ns/op |                op/s |    err% |     total | sgemv:T
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |       15,838,985.00 |               63.14 |    4.4% |      0.18 | `cblas`
|    94.0% |       16,858,497.00 |               59.32 |    1.1% |      0.19 | `meatballs`
|    18.5% |       85,764,201.00 |               11.66 |    1.1% |      0.94 | `naive`

| relative |               ns/op |                op/s |    err% |     total | ssymv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        8,936,404.00 |              111.90 |    6.5% |      0.10 | :wavy_dash: `cblas` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    48.6% |       18,379,115.00 |               54.41 |    1.6% |      0.21 | `meatballs`
|    16.7% |       53,530,625.00 |               18.68 |    1.9% |      0.59 | `naive`

| relative |               ns/op |                op/s |    err% |     total | ssymv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        8,976,008.00 |              111.41 |    3.4% |      0.10 | `cblas`
|    48.3% |       18,566,423.00 |               53.86 |    4.6% |      0.21 | `meatballs`
|    12.4% |       72,424,771.00 |               13.81 |    1.1% |      0.80 | `naive`

| relative |               ns/op |                op/s |    err% |     total | strmv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        8,930,108.00 |              111.98 |    5.9% |      0.10 | :wavy_dash: `cblas` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|   102.9% |        8,679,205.00 |              115.22 |    3.0% |      0.10 | `meatballs`
|    21.5% |       41,487,399.00 |               24.10 |    2.0% |      0.46 | `naive`

| relative |               ns/op |                op/s |    err% |     total | strmv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |        8,322,000.00 |              120.16 |    3.6% |      0.10 | `cblas`
|    95.8% |        8,687,704.00 |              115.11 |    2.8% |      0.10 | `meatballs`
|    20.1% |       41,367,798.00 |               24.17 |    0.8% |      0.46 | `naive`

## size = 16384

| relative |               ns/op |                op/s |    err% |     total | sgemv:N
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |       55,379,066.00 |               18.06 |    2.8% |      0.61 | `cblas`
|    86.0% |       64,420,637.00 |               15.52 |    4.2% |      0.72 | `meatballs`
|     1.9% |    2,898,804,546.00 |                0.34 |    1.1% |     31.80 | `naive`

| relative |               ns/op |                op/s |    err% |     total | sgemv:T
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |       71,011,561.00 |               14.08 |    0.4% |      0.79 | `cblas`
|   113.7% |       62,452,382.00 |               16.01 |    3.9% |      0.68 | `meatballs`
|    24.7% |      286,945,174.00 |                3.48 |    0.3% |      3.17 | `naive`

| relative |               ns/op |                op/s |    err% |     total | ssymv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |       30,443,984.00 |               32.85 |    5.4% |      0.35 | :wavy_dash: `cblas` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    48.8% |       62,368,682.00 |               16.03 |    2.6% |      0.69 | `meatballs`
|    17.2% |      177,492,848.00 |                5.63 |    0.7% |      1.96 | `naive`

| relative |               ns/op |                op/s |    err% |     total | ssymv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |       32,464,756.00 |               30.80 |    2.1% |      0.37 | `cblas`
|    53.9% |       60,221,862.00 |               16.61 |    2.0% |      0.67 | `meatballs`
|    13.3% |      243,570,174.00 |                4.11 |    0.9% |      2.67 | `naive`

| relative |               ns/op |                op/s |    err% |     total | strmv:U
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |       30,640,137.00 |               32.64 |    1.8% |      0.34 | `cblas`
|   103.4% |       29,635,425.00 |               33.74 |    3.2% |      0.34 | `meatballs`
|    21.9% |      139,777,235.00 |                7.15 |    1.2% |      1.55 | `naive`

| relative |               ns/op |                op/s |    err% |     total | strmv:L
|---------:|--------------------:|--------------------:|--------:|----------:|:--------
|   100.0% |       29,672,625.00 |               33.70 |    1.2% |      0.33 | `cblas`
|    91.8% |       32,324,255.00 |               30.94 |    6.2% |      0.35 | :wavy_dash: `meatballs` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|    21.1% |      140,961,848.00 |                7.09 |    0.7% |      1.55 | `naive`