# Level 1
## size = 1

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                4.40 |      227,209,288.40 |    5.4% |      0.02 | :wavy_dash: `cblas` (Unstable with ~217,404.4 iters. Increase `minEpochIterations` to e.g. 2174044)
|    66.7% |                6.60 |      151,534,391.33 |    2.2% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                4.56 |      219,385,198.93 |    0.7% |      0.02 | `cblas`
|    84.0% |                5.43 |      184,217,040.69 |    1.0% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                2.84 |      351,545,486.02 |    0.7% |      0.02 | `cblas`
|    36.8% |                7.73 |      129,376,314.57 |   23.9% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~119,394.5 iters. Increase `minEpochIterations` to e.g. 1193945)

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                2.08 |      481,876,889.32 |    2.8% |      0.01 | `cblas`
|    32.3% |                6.43 |      155,409,630.29 |    3.0% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |                4.45 |      224,590,663.46 |    0.9% |      0.02 | `cblas`
|    68.1% |                6.54 |      152,946,661.99 |    6.1% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~123,390.2 iters. Increase `minEpochIterations` to e.g. 1233902)

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |                5.74 |      174,081,409.65 |    1.7% |      0.02 | `cblas`
|    91.7% |                6.26 |      159,652,367.07 |    1.3% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                4.60 |      217,294,791.92 |    2.4% |      0.01 | `cblas`
|    63.9% |                7.21 |      138,777,698.49 |   28.2% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~105,901.7 iters. Increase `minEpochIterations` to e.g. 1059017)

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                3.96 |      252,613,001.27 |    0.9% |      0.01 | `cblas`
|    92.0% |                4.30 |      232,470,422.62 |    2.5% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |                7.04 |      142,117,391.81 |    5.5% |      0.01 | :wavy_dash: `cblas` (Unstable with ~60,675.9 iters. Increase `minEpochIterations` to e.g. 606759)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 2

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                4.02 |      248,744,365.99 |    0.8% |      0.02 | `cblas`
|    62.3% |                6.46 |      154,853,129.30 |    0.4% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                4.74 |      211,037,718.51 |    0.2% |      0.01 | `cblas`
|    10.3% |               46.16 |       21,665,873.27 |    8.7% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~10,298.5 iters. Increase `minEpochIterations` to e.g. 102985)

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                3.74 |      267,660,551.69 |    3.6% |      0.01 | `cblas`
|    59.5% |                6.28 |      159,313,429.01 |    0.7% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                7.06 |      141,717,773.59 |    3.7% |      0.01 | `cblas`
|    10.8% |               65.15 |       15,349,635.71 |   13.5% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~8,792.2 iters. Increase `minEpochIterations` to e.g. 87922)

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |                6.12 |      163,268,769.89 |   10.2% |      0.01 | :wavy_dash: `cblas` (Unstable with ~184,595.8 iters. Increase `minEpochIterations` to e.g. 1845958)
|    96.5% |                6.35 |      157,541,647.62 |    3.6% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |                7.72 |      129,484,687.77 |   17.7% |      0.01 | :wavy_dash: `cblas` (Unstable with ~122,140.6 iters. Increase `minEpochIterations` to e.g. 1221406)
|   123.6% |                6.25 |      160,062,211.23 |    0.7% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                4.12 |      242,908,166.64 |    1.4% |      0.01 | `cblas`
|    74.1% |                5.56 |      179,998,068.88 |    1.5% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                5.10 |      196,229,224.31 |    9.2% |      0.02 | :wavy_dash: `cblas` (Unstable with ~192,543.4 iters. Increase `minEpochIterations` to e.g. 1925434)
|   117.4% |                4.34 |      230,313,870.43 |    3.7% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |                7.86 |      127,238,356.39 |    2.5% |      0.02 | `cblas`
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 4

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                6.59 |      151,854,196.92 |    6.1% |      0.01 | :wavy_dash: `cblas` (Unstable with ~168,165.3 iters. Increase `minEpochIterations` to e.g. 1681653)
|   105.3% |                6.25 |      159,958,332.18 |    3.2% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                6.66 |      150,210,420.30 |    2.0% |      0.01 | `cblas`
|    12.0% |               55.62 |       17,978,318.83 |   38.4% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~15,387.0 iters. Increase `minEpochIterations` to e.g. 153870)

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                4.94 |      202,350,992.72 |    1.3% |      0.02 | `cblas`
|    67.0% |                7.37 |      135,657,539.92 |   31.5% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~138,689.7 iters. Increase `minEpochIterations` to e.g. 1386897)

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                7.62 |      131,317,705.34 |    1.0% |      0.02 | `cblas`
|    16.5% |               46.07 |       21,708,042.56 |    6.3% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~14,239.2 iters. Increase `minEpochIterations` to e.g. 142392)

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |                6.19 |      161,544,013.70 |    0.9% |      0.01 | `cblas`
|   102.6% |                6.03 |      165,774,984.97 |    0.3% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |                6.88 |      145,381,170.33 |    0.5% |      0.02 | `cblas`
|   113.3% |                6.07 |      164,644,281.57 |    1.9% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                4.21 |      237,300,834.32 |    1.1% |      0.01 | `cblas`
|    78.0% |                5.40 |      185,057,592.48 |    0.4% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                8.26 |      121,056,461.52 |   20.4% |      0.01 | :wavy_dash: `cblas` (Unstable with ~78,253.6 iters. Increase `minEpochIterations` to e.g. 782536)
|   172.5% |                4.79 |      208,840,663.05 |    8.2% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~198,913.1 iters. Increase `minEpochIterations` to e.g. 1989131)

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |                7.74 |      129,143,842.75 |    5.2% |      0.02 | :wavy_dash: `cblas` (Unstable with ~120,557.8 iters. Increase `minEpochIterations` to e.g. 1205578)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 8

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                6.86 |      145,768,752.73 |    1.1% |      0.02 | `cblas`
|    55.6% |               12.33 |       81,078,103.81 |    1.1% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                5.99 |      166,909,108.46 |    2.0% |      0.02 | `cblas`
|   177.4% |                3.38 |      296,100,432.40 |    0.9% |      0.00 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                7.66 |      130,589,912.03 |   35.6% |      0.02 | :wavy_dash: `cblas` (Unstable with ~141,488.4 iters. Increase `minEpochIterations` to e.g. 1414884)
|    91.7% |                8.35 |      119,811,124.02 |   30.8% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~151,812.6 iters. Increase `minEpochIterations` to e.g. 1518126)

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                1.97 |      506,987,129.68 |    1.1% |      0.02 | `cblas`
|    15.3% |               12.89 |       77,601,463.14 |    5.0% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |                9.53 |      104,976,178.42 |    9.9% |      0.01 | :wavy_dash: `cblas` (Unstable with ~98,197.7 iters. Increase `minEpochIterations` to e.g. 981977)
|   131.3% |                7.26 |      137,802,664.52 |    1.3% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |                8.98 |      111,373,886.99 |    1.8% |      0.01 | `cblas`
|   121.7% |                7.38 |      135,508,144.84 |    3.3% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                5.08 |      196,980,983.19 |    3.1% |      0.02 | `cblas`
|    77.5% |                6.55 |      152,680,740.41 |    0.5% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                5.02 |      199,142,088.34 |    2.6% |      0.02 | `cblas`
|    99.8% |                5.03 |      198,683,551.36 |    0.6% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |                8.76 |      114,091,478.09 |    0.4% |      0.02 | `cblas`
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 16

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                6.80 |      147,084,799.53 |    1.4% |      0.02 | `cblas`
|   103.0% |                6.60 |      151,511,276.71 |    3.4% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                7.42 |      134,856,445.49 |    1.0% |      0.01 | `cblas`
|     4.4% |              168.70 |        5,927,546.28 |   63.7% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~5,646.4 iters. Increase `minEpochIterations` to e.g. 56464)

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                5.87 |      170,408,223.58 |    4.1% |      0.01 | `cblas`
|    96.9% |                6.06 |      165,098,719.12 |    1.0% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               34.84 |       28,704,061.90 |   69.9% |      0.01 | :wavy_dash: `cblas` (Unstable with ~13,790.5 iters. Increase `minEpochIterations` to e.g. 137905)
|   516.9% |                6.74 |      148,385,282.51 |    1.7% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |               13.49 |       74,147,253.79 |    0.4% |      0.01 | `cblas`
|   153.1% |                8.81 |      113,544,753.66 |    1.2% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |               14.90 |       67,133,743.06 |    1.2% |      0.02 | `cblas`
|   169.9% |                8.77 |      114,062,802.98 |    0.9% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                6.76 |      147,985,901.86 |    2.4% |      0.02 | `cblas`
|    81.6% |                8.28 |      120,805,369.13 |   19.6% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~63,047.5 iters. Increase `minEpochIterations` to e.g. 630475)

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                5.79 |      172,645,745.15 |    9.7% |      0.02 | :wavy_dash: `cblas` (Unstable with ~173,019.2 iters. Increase `minEpochIterations` to e.g. 1730192)
|    67.1% |                8.64 |      115,791,668.69 |   33.6% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~107,120.0 iters. Increase `minEpochIterations` to e.g. 1071200)

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |               10.52 |       95,037,144.49 |    9.8% |      0.01 | :wavy_dash: `cblas` (Unstable with ~81,688.6 iters. Increase `minEpochIterations` to e.g. 816886)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 32

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                8.70 |      114,998,859.14 |    8.3% |      0.01 | :wavy_dash: `cblas` (Unstable with ~49,368.1 iters. Increase `minEpochIterations` to e.g. 493681)
|    42.0% |               20.71 |       48,293,635.32 |   66.2% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~32,886.6 iters. Increase `minEpochIterations` to e.g. 328866)

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                7.22 |      138,416,820.42 |    9.1% |      0.02 | :wavy_dash: `cblas` (Unstable with ~137,363.0 iters. Increase `minEpochIterations` to e.g. 1373630)
|   130.8% |                5.52 |      181,054,610.98 |   32.6% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~99,750.0 iters. Increase `minEpochIterations` to e.g. 997500)

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                7.04 |      142,052,028.88 |    5.1% |      0.01 | :wavy_dash: `cblas` (Unstable with ~116,193.7 iters. Increase `minEpochIterations` to e.g. 1161937)
|   108.5% |                6.49 |      154,122,776.70 |    0.5% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                8.49 |      117,804,765.53 |    3.9% |      0.02 | `cblas`
|   108.8% |                7.80 |      128,199,540.80 |   11.4% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~115,889.1 iters. Increase `minEpochIterations` to e.g. 1158891)

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |               10.48 |       95,427,951.42 |    7.1% |      0.02 | :wavy_dash: `cblas` (Unstable with ~96,893.3 iters. Increase `minEpochIterations` to e.g. 968933)
|    88.6% |               11.83 |       84,523,096.09 |   45.8% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~49,880.8 iters. Increase `minEpochIterations` to e.g. 498808)

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |               16.78 |       59,603,987.98 |   47.4% |      0.01 | :wavy_dash: `cblas` (Unstable with ~45,668.3 iters. Increase `minEpochIterations` to e.g. 456683)
|   181.2% |                9.26 |      108,026,891.37 |   18.0% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~110,093.6 iters. Increase `minEpochIterations` to e.g. 1100936)

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               12.70 |       78,735,472.34 |    7.0% |      0.01 | :wavy_dash: `cblas` (Unstable with ~77,259.4 iters. Increase `minEpochIterations` to e.g. 772594)
|   160.2% |                7.93 |      126,116,880.35 |   16.9% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~141,605.3 iters. Increase `minEpochIterations` to e.g. 1416053)

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                9.98 |      100,153,338.07 |   15.4% |      0.01 | :wavy_dash: `cblas` (Unstable with ~100,700.2 iters. Increase `minEpochIterations` to e.g. 1007002)
|   176.5% |                5.66 |      176,729,170.65 |    0.6% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |               14.01 |       71,400,036.41 |   15.6% |      0.02 | :wavy_dash: `cblas` (Unstable with ~72,456.7 iters. Increase `minEpochIterations` to e.g. 724567)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 64

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               13.99 |       71,496,492.60 |   13.0% |      0.01 | :wavy_dash: `cblas` (Unstable with ~42,694.3 iters. Increase `minEpochIterations` to e.g. 426943)
|   100.6% |               13.90 |       71,921,376.86 |   10.3% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~79,008.9 iters. Increase `minEpochIterations` to e.g. 790089)

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               10.73 |       93,187,873.28 |    9.0% |      0.01 | :wavy_dash: `cblas` (Unstable with ~95,981.3 iters. Increase `minEpochIterations` to e.g. 959813)
|   157.5% |                6.82 |      146,726,624.96 |    9.8% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~160,113.2 iters. Increase `minEpochIterations` to e.g. 1601132)

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                9.96 |      100,374,435.58 |   13.9% |      0.01 | :wavy_dash: `cblas` (Unstable with ~77,121.6 iters. Increase `minEpochIterations` to e.g. 771216)
|    82.1% |               12.14 |       82,401,934.44 |   11.1% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~57,620.7 iters. Increase `minEpochIterations` to e.g. 576207)

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               10.31 |       97,024,908.87 |    8.8% |      0.02 | :wavy_dash: `cblas` (Unstable with ~94,011.5 iters. Increase `minEpochIterations` to e.g. 940115)
|    96.1% |               10.73 |       93,203,482.63 |   10.9% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~102,415.3 iters. Increase `minEpochIterations` to e.g. 1024153)

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |               10.04 |       99,553,261.93 |    6.8% |      0.02 | :wavy_dash: `cblas` (Unstable with ~99,697.7 iters. Increase `minEpochIterations` to e.g. 996977)
|    82.3% |               12.20 |       81,981,992.00 |    7.6% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~93,545.2 iters. Increase `minEpochIterations` to e.g. 935452)

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |               15.14 |       66,056,371.39 |    0.8% |      0.01 | `cblas`
|   168.7% |                8.97 |      111,448,671.18 |    1.1% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               21.20 |       47,160,189.46 |    9.2% |      0.02 | :wavy_dash: `cblas` (Unstable with ~50,731.5 iters. Increase `minEpochIterations` to e.g. 507315)
|   171.8% |               12.34 |       81,040,110.08 |   23.4% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~89,278.3 iters. Increase `minEpochIterations` to e.g. 892783)

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |                9.20 |      108,718,332.17 |    9.2% |      0.02 | :wavy_dash: `cblas` (Unstable with ~113,764.3 iters. Increase `minEpochIterations` to e.g. 1137643)
|   111.8% |                8.23 |      121,563,778.83 |    9.7% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~99,631.7 iters. Increase `minEpochIterations` to e.g. 996317)

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |               22.77 |       43,921,521.82 |   18.2% |      0.01 | :wavy_dash: `cblas` (Unstable with ~54,125.6 iters. Increase `minEpochIterations` to e.g. 541256)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 256

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               35.06 |       28,518,678.82 |    1.7% |      0.02 | `cblas`
|   151.9% |               23.08 |       43,330,637.55 |   13.2% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~23,034.4 iters. Increase `minEpochIterations` to e.g. 230344)

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               25.30 |       39,532,276.15 |   35.4% |      0.02 | :wavy_dash: `cblas` (Unstable with ~43,306.5 iters. Increase `minEpochIterations` to e.g. 433065)
|   159.5% |               15.85 |       63,072,067.33 |   33.8% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~20,565.7 iters. Increase `minEpochIterations` to e.g. 205657)

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               21.45 |       46,614,898.42 |    8.9% |      0.02 | :wavy_dash: `cblas` (Unstable with ~44,375.0 iters. Increase `minEpochIterations` to e.g. 443750)
|   135.1% |               15.87 |       62,993,697.51 |    8.0% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~55,683.9 iters. Increase `minEpochIterations` to e.g. 556839)

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               17.35 |       57,632,016.25 |    1.7% |      0.02 | `cblas`
|    96.6% |               17.96 |       55,676,443.72 |    6.7% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~59,183.9 iters. Increase `minEpochIterations` to e.g. 591839)

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |               22.02 |       45,408,868.09 |   11.3% |      0.01 | :wavy_dash: `cblas` (Unstable with ~36,319.3 iters. Increase `minEpochIterations` to e.g. 363193)
|   104.7% |               21.03 |       47,552,435.70 |   20.2% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~39,309.6 iters. Increase `minEpochIterations` to e.g. 393096)

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |               44.49 |       22,476,891.74 |   10.8% |      0.02 | :wavy_dash: `cblas` (Unstable with ~20,486.5 iters. Increase `minEpochIterations` to e.g. 204865)
|   212.1% |               20.98 |       47,671,420.20 |    8.9% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~49,132.4 iters. Increase `minEpochIterations` to e.g. 491324)

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               87.99 |       11,364,878.56 |   36.9% |      0.02 | :wavy_dash: `cblas` (Unstable with ~13,193.4 iters. Increase `minEpochIterations` to e.g. 131934)
|   563.8% |               15.61 |       64,075,340.40 |    2.2% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               13.04 |       76,666,942.71 |    6.0% |      0.01 | :wavy_dash: `cblas` (Unstable with ~69,299.5 iters. Increase `minEpochIterations` to e.g. 692995)
|    82.0% |               15.90 |       62,891,009.54 |   14.8% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~65,831.9 iters. Increase `minEpochIterations` to e.g. 658319)

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |               41.41 |       24,150,821.79 |   29.5% |      0.01 | :wavy_dash: `cblas` (Unstable with ~12,447.6 iters. Increase `minEpochIterations` to e.g. 124476)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 1024

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              163.37 |        6,120,906.80 |   19.9% |      0.01 | :wavy_dash: `cblas` (Unstable with ~3,791.7 iters. Increase `minEpochIterations` to e.g. 37917)
|   206.5% |               79.11 |       12,640,736.95 |    6.7% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~4,405.1 iters. Increase `minEpochIterations` to e.g. 44051)

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               75.71 |       13,207,896.36 |    8.8% |      0.02 | :wavy_dash: `cblas` (Unstable with ~14,128.5 iters. Increase `minEpochIterations` to e.g. 141285)
|    58.7% |              128.88 |        7,759,174.94 |    4.4% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               89.64 |       11,156,109.99 |   34.6% |      0.01 | :wavy_dash: `cblas` (Unstable with ~5,676.9 iters. Increase `minEpochIterations` to e.g. 56769)
|   108.4% |               82.68 |       12,094,342.58 |    6.9% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~12,711.0 iters. Increase `minEpochIterations` to e.g. 127110)

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               62.69 |       15,952,777.51 |    1.0% |      0.02 | `cblas`
|    60.8% |              103.13 |        9,696,390.73 |    2.2% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |               56.48 |       17,704,315.89 |    1.6% |      0.01 | `cblas`
|    54.3% |              104.06 |        9,610,105.78 |   45.0% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~14,243.9 iters. Increase `minEpochIterations` to e.g. 142439)

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |              288.77 |        3,462,965.32 |   58.7% |      0.02 | :wavy_dash: `cblas` (Unstable with ~3,188.1 iters. Increase `minEpochIterations` to e.g. 31881)
|   325.6% |               88.69 |       11,275,010.64 |   23.2% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~9,158.5 iters. Increase `minEpochIterations` to e.g. 91585)

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              296.53 |        3,372,335.98 |   30.2% |      0.00 | :wavy_dash: `cblas` (Unstable with ~308.4 iters. Increase `minEpochIterations` to e.g. 3084)
|   540.9% |               54.82 |       18,241,195.97 |   48.1% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~14,162.5 iters. Increase `minEpochIterations` to e.g. 141625)

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |               44.96 |       22,240,471.73 |   17.4% |      0.02 | :wavy_dash: `cblas` (Unstable with ~25,437.0 iters. Increase `minEpochIterations` to e.g. 254370)
|    91.5% |               49.12 |       20,357,159.79 |   16.9% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~19,725.9 iters. Increase `minEpochIterations` to e.g. 197259)

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |              108.04 |        9,256,198.35 |   40.0% |      0.01 | :wavy_dash: `cblas` (Unstable with ~2,431.6 iters. Increase `minEpochIterations` to e.g. 24316)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 4096

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              706.30 |        1,415,820.79 |   10.4% |      0.02 | :wavy_dash: `cblas` (Unstable with ~1,096.3 iters. Increase `minEpochIterations` to e.g. 10963)
|   242.6% |              291.15 |        3,434,650.46 |    1.7% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              295.44 |        3,384,833.47 |    4.6% |      0.02 | `cblas`
|   208.9% |              141.40 |        7,072,152.65 |    3.1% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              344.78 |        2,900,435.77 |    2.0% |      0.02 | `cblas`
|   105.1% |              327.93 |        3,049,391.55 |    5.4% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~2,977.4 iters. Increase `minEpochIterations` to e.g. 29774)

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              204.93 |        4,879,722.83 |    2.0% |      0.01 | `cblas`
|    50.7% |              403.92 |        2,475,752.91 |    1.3% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |              219.53 |        4,555,156.28 |    4.6% |      0.02 | `cblas`
|    91.5% |              239.99 |        4,166,821.22 |    1.1% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |              605.66 |        1,651,101.59 |    1.5% |      0.02 | `cblas`
|   251.2% |              241.15 |        4,146,795.43 |    1.6% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              908.81 |        1,100,346.02 |    2.8% |      0.02 | `cblas`
|   700.3% |              129.77 |        7,705,817.60 |    0.5% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              177.20 |        5,643,476.44 |    8.0% |      0.02 | :wavy_dash: `cblas` (Unstable with ~5,970.6 iters. Increase `minEpochIterations` to e.g. 59706)
|   126.4% |              140.23 |        7,130,979.59 |    1.5% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |              268.75 |        3,720,872.58 |    0.4% |      0.02 | `cblas`
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 8192

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |            1,570.13 |          636,891.65 |    8.2% |      0.01 | :wavy_dash: `cblas` (Unstable with ~643.2 iters. Increase `minEpochIterations` to e.g. 6432)
|   161.6% |              971.35 |        1,029,496.82 |   10.4% |      0.00 | :wavy_dash: `meatballs` (Unstable with ~144.0 iters. Increase `minEpochIterations` to e.g. 1440)

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              573.56 |        1,743,508.21 |    2.6% |      0.02 | `cblas`
|   201.5% |              284.64 |        3,513,169.61 |    2.7% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              830.70 |        1,203,797.90 |    2.2% |      0.02 | `cblas`
|   111.6% |              744.30 |        1,343,552.75 |    1.0% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              970.99 |        1,029,872.92 |    2.3% |      0.02 | `cblas`
|    94.5% |            1,027.86 |          972,895.86 |    3.0% |      0.01 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |              634.58 |        1,575,837.16 |    3.4% |      0.02 | `cblas`
|    67.8% |              936.12 |        1,068,238.66 |   10.3% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~916.8 iters. Increase `minEpochIterations` to e.g. 9168)

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |            1,322.39 |          756,209.06 |    4.6% |      0.02 | `cblas`
|   144.7% |              913.95 |        1,094,150.07 |    6.0% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~1,006.9 iters. Increase `minEpochIterations` to e.g. 10069)

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |            1,854.19 |          539,320.43 |    4.0% |      0.02 | `cblas`
|   692.2% |              267.87 |        3,733,129.44 |    1.1% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              355.86 |        2,810,113.25 |    2.6% |      0.02 | `cblas`
|   120.0% |              296.51 |        3,372,578.81 |    9.8% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~1,680.0 iters. Increase `minEpochIterations` to e.g. 16800)

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |              595.50 |        1,679,252.07 |    5.3% |      0.01 | :wavy_dash: `cblas` (Unstable with ~587.3 iters. Increase `minEpochIterations` to e.g. 5873)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)

## size = 16384

| relative |               ns/op |                op/s |    err% |     total | sswap
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |            3,038.10 |          329,153.61 |    6.6% |      0.01 | :wavy_dash: `cblas` (Unstable with ~135.2 iters. Increase `minEpochIterations` to e.g. 1352)
|   146.1% |            2,079.55 |          480,874.32 |    1.4% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sscal
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |            1,638.46 |          610,328.64 |   25.0% |      0.01 | :wavy_dash: `cblas` (Unstable with ~348.3 iters. Increase `minEpochIterations` to e.g. 3483)
|   156.4% |            1,047.61 |          954,553.36 |    5.0% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | scopy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |            1,771.46 |          564,506.67 |    3.4% |      0.02 | `cblas`
|   102.4% |            1,729.31 |          578,265.20 |    3.0% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | saxpy
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |            1,585.27 |          630,808.22 |    3.9% |      0.02 | `cblas`
|    56.5% |            2,805.75 |          356,410.66 |   29.6% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~333.2 iters. Increase `minEpochIterations` to e.g. 3332)

| relative |               ns/op |                op/s |    err% |     total | sdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-----
|   100.0% |            2,552.12 |          391,831.31 |   76.5% |      0.02 | :wavy_dash: `cblas` (Unstable with ~293.1 iters. Increase `minEpochIterations` to e.g. 2931)
|   111.3% |            2,292.28 |          436,247.08 |   25.8% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~394.0 iters. Increase `minEpochIterations` to e.g. 3940)

| relative |               ns/op |                op/s |    err% |     total | sdsdot
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |            2,892.51 |          345,719.90 |    2.5% |      0.02 | `cblas`
|   148.3% |            1,950.29 |          512,744.22 |    9.3% |      0.02 | :wavy_dash: `meatballs` (Unstable with ~410.0 iters. Increase `minEpochIterations` to e.g. 4100)

| relative |               ns/op |                op/s |    err% |     total | snrm2
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |            5,125.00 |          195,121.82 |   40.1% |      0.02 | :wavy_dash: `cblas` (Unstable with ~227.9 iters. Increase `minEpochIterations` to e.g. 2279)
|   811.5% |              631.58 |        1,583,324.17 |    1.9% |      0.02 | `meatballs`

| relative |               ns/op |                op/s |    err% |     total | sasum
|---------:|--------------------:|--------------------:|--------:|----------:|:------
|   100.0% |              740.04 |        1,351,286.94 |   12.2% |      0.01 | :wavy_dash: `cblas` (Unstable with ~838.8 iters. Increase `minEpochIterations` to e.g. 8388)
|   114.8% |              644.47 |        1,551,661.19 |    6.7% |      0.01 | :wavy_dash: `meatballs` (Unstable with ~867.2 iters. Increase `minEpochIterations` to e.g. 8672)

| relative |               ns/op |                op/s |    err% |     total | isamax
|---------:|--------------------:|--------------------:|--------:|----------:|:-------
|   100.0% |            1,629.23 |          613,786.59 |   28.4% |      0.02 | :wavy_dash: `cblas` (Unstable with ~555.6 iters. Increase `minEpochIterations` to e.g. 5556)
|        - |                   - |                   - |       - |         - | :boom: `meatballs` (iterations overflow. Maybe your code got optimized away?)