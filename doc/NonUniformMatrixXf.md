# NonUniformMatrixXf
非等宽矩阵类，用于处理非均匀网格数据。

## 数据结构
### 成员变量
- `Eigen::VectorXf x_coords`: 列坐标(U方向)，表示单元格中心坐标
- `Eigen::VectorXf y_coords`: 行坐标(V方向)，表示单元格中心坐标
- 继承自 `RowMatrixXf` 的值矩阵

### 错误代码
```cpp
enum ErrorCode {
    SUCCESS            = 0,  // 操作成功
    FILE_NOT_OPEN      = 1,  // 文件打开失败
    INVALID_DIMENSIONS = 2,  // 无效的维度
    READ_ERROR         = 3,  // 读取错误
    WRITE_ERROR        = 4   // 写入错误
}
```

## 文件格式
```
rows cols           // 第1行：矩阵维度
    x1 x2 ... xn   // 第2行：列坐标数组(长度为cols)
y1  v11 v12 ... v1n // 第3行开始：每行首个数为行坐标，后跟该行数据
y2  v21 v22 ... v2n
...
ym  vm1 vm2 ... vmn
```

## 公共接口

### 构造函数
```cpp
NonUniformMatrixXf();  // 默认构造函数
```

### 数据操作
```cpp
void fill_pattern();   // 填充示例数据
```

### 文件操作
```cpp
int read(const std::string& path);    // 从文件读取
int read(std::ifstream& file);        // 从流读取(支持连续读取多个矩阵)
int save(const std::string& path) const;  // 保存到文件
```

### 输出格式化
```cpp
friend std::ostream& operator<<(std::ostream& os, const NonUniformMatrixXf& matrix);
```

## 使用示例

### 基本操作
```cpp
NonUniformMatrixXf matrix;
matrix.fill_pattern();
std::cout << matrix << std::endl;
```

### 文件操作
```cpp
// 单个矩阵读写
NonUniformMatrixXf matrix;
matrix.read("input.txt");
matrix.save("output.txt");

// 连续读取多个矩阵
std::ifstream file("matrices.txt");
NonUniformMatrixXf matrix1, matrix2;
matrix1.read(file);
matrix2.read(file);
file.close();
```

### 输出示例
```
6       11
        0.0    2.0    4.0   10.0   20.0   40.0   60.0   80.0   85.0   88.0   90.0
  0     0.0    0.5    1.2    3.4    8.1    9.2    9.8   10.0   12.0   15.0   18.0
  1     0.3    1.1    2.5    4.8    9.3   10.0   11.0   13.0   14.0   16.0   19.0
  5     1.5    2.8    4.2    7.5   12.0   13.0   14.0   15.0   16.0   17.0   19.0
 10     3.2    4.5    6.8   11.0   15.0   16.0   16.0   17.0   18.0   19.0   20.0
 30     8.5    9.2   11.0   14.0   17.0   18.0   18.0   19.0   19.0   20.0   20.0
 45    12.0   13.0   15.0   16.0   18.0   19.0   19.0   20.0   20.0   20.0   20.0
```


