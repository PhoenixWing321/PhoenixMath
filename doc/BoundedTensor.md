

# 多层矩阵


- 继承于 `Phoenix::RowTensor3f`
- 添加成员 `Bounds2f bounds`  
- BoundedTensor.h 和 BoundedTensor.cpp 文件

# 稠密矩阵和稀疏矩阵

- 在 Eigen 中，`Dense` 表示稠密矩阵（Dense Matrix），与稀疏矩阵（Sparse Matrix）相对。

稠密矩阵（Dense Matrix）：
- 矩阵中大多数元素都是非零值
- 所有元素都被存储在内存中
- 适用于大多数元素都有值的情况
- 存储方式简单，访问速度快
- 例如：图像数据、普通的数值计算等

稀疏矩阵（Sparse Matrix）：
- 矩阵中大多数元素为零
- 只存储非零元素及其位置信息
- 适用于大多数元素为零的情况
- 节省内存空间，但访问较复杂
- 例如：大型网络连接矩阵、有限元分析等 