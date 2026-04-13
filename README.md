# C++ Binary-Coded Genetic Algorithm

## 功能實作狀況

本專案將 GA 的核心管線（Pipeline）進行了完整的封裝，並提供靈活的 API 供外部呼叫。

### 已實作部分
* **核心編碼機制**：二進位轉浮點數解碼（支援任意維度與自訂搜尋上下界）。
* **菁英保留機制 (Elitism)**：交配階段結合 Cloning 策略，並在世代交替時保留初始族群大小的高適應度個體，保證收斂方向。
* **多樣化的父代選擇 (Selection Methods)**：
    * 錦標賽選擇 (Tournament Selection) - *預設*
    * 標準輪盤法 (Default Roulette Wheel)
    * 排名輪盤法 (Rank-based Roulette)
    * 隨機 (Random)
    * 最佳 (Best)
* **交配與突變 (Crossover & Mutation)**：
    * 單點交配 (Single-Point Crossover)
    * 常數機率位元翻轉突變 (Constant Probability Bit-Flip Mutation)
* **工程與分析工具**：
    * 提供 `GA_Wrapper`，支援泛型（Template）目標函數傳入。
    * 內建 CSV 匯出功能，可記錄每代最佳適應度、原始目標函數值及染色體數據，便於繪製學習曲線。
    * 支援 CMake `Debug` / `Release` 多重建置模式。

### 未實作部分
* **交配機制擴充**：多點交配 (Multi-Point Crossover) 與均勻交配 (Uniform Crossover)。
* **動態突變率**：隨世代數遞減的突變機率 (Decreasing Mutation Probability)，以強化演算法後期的局部搜尋 (Exploitation) 能力。

### TODO:
* **平行運算加速**：引入 OpenMP 或 dispatch(Apple silicon)。
* **實數編碼支援**：加入實數編碼 (Real-value encoding) 介面。

---

## 測試函數

1. **Rastrigin's Function**
    * **方程式**: $$f(\mathbf{x}) = 10n_{var} + \sum_{i=1}^{n_{var}} \left( x_i^2 - 10 \cos(2\pi x_i) \right)$$
    * **$x_i$ 的範圍**: [5.12, -5.12]
    * **特徵**: 在 $x_i$ 皆為 0 時，輸出為 0。
2. **Schwefel's Function**
    * **方程式**: $$f(x) = 418.9829n_{var} - \sum_{i=1}^{n_{var}} x_i \sin(\sqrt{|x_i|})$$
    * **$x_i$ 的範圍**: [500, -500]
    * **特徵**: 在 $x_i$ 皆為 420.9687 時，輸出為 0。

---

## 建置與編譯

本專案使用 **CMake** 進行建置
### 系統需求
* **CMake** >= 3.20
* **Compiler**: 支援 C++17 的編譯器 (Apple Clang, GCC 等)

### 編譯步驟

1. **建立建置目錄及編譯**

    在專案根目錄下執行：
    ```bash
    cmake -B build
    cmake --build build
    ```
2. **執行可執行檔**
    ```bash
    ./build/bin/Rastrigin
    ./build/bin/Schwefel
    ```

---

## 專案架構與檔案說明

```text
.
├── CMakeLists.txt         # CMake 專案建置腳本
├── README.md              # 說明文件
├── Schwefel.cpp           # 主程式範例：Schwefel's Function測試
├── Rastrigin.cpp          # 主程式範例：Rastrigin's Function測試
│
├── include/               # 標頭檔目錄 (Header Files)
│   ├── GA_BIN.hpp         # 核心標頭檔：宣告 Params、Population 結構
│   └── GA_Wrapper.hpp     # 宣告 run_ga 包裝函式與 CSV writter
│
├── src/                   # 原始碼目錄 (Source Files)
│   ├── GA_BIN.cpp         # GA 核心實作
│   └── GA_BIN_wrapper.cpp # 輔助工具實作：包含字串轉換、CSV 輸出處理等周邊輔助功能
│
└── test/                   # 測試程式
    ├── test_GA_BIN.cpp     # 單元測試與流程測試
    └── performance.cpp     # 效能評估：測試大族群、高世代數下的演算法執行時間與瓶頸
