## 一、作业说明

1.使用作业二的语料，从前10000行中获取8:2的训练集和测试集。

2.原始语料处理为CRF++标准格式等处理程序在SourceCode文件夹中。

3.将词语处理为单字词，处理后标准格式第一列为单字、第二列为分词标注、第三列为词性标注、第四列为人名标注。

4.template文件考虑上下文、分词和词性因素，效果非常好，5-fold交叉验证结果如下：

(1) precision = 1 recall = 1 F-score = 1 人名正确预测数：4003 预测为人名数：4003 测试集实际标注为人名数：4003

(2) precision = 1 recall = 1 F-score = 1 人名正确预测数：3147 预测为人名数：3147 测试集实际标注为人名数：3147

(3) precision = 1 recall = 1 F-score = 1 人名正确预测数：3411 预测为人名数：3411 测试集实际标注为人名数：3411

(4) precision = 1 recall = 1 F-score = 1 人名正确预测数：4356 预测为人名数：4356 测试集实际标注为人名数：4356

(5) precision = 1 recall = 1 F-score = 1 人名正确预测数：5291 预测为人名数：5291 测试集实际标注为人名数：5291

结果可以看出，在同时考虑上下文、分词以及词性的情况下，中文人名识别的正确率可达到接近100%，而且迭代速度比较快，一般在50次以内。

如果只考虑上下文，不考虑词性和分词，以第五次交叉验证数据做测试，结果为（precision = 0.934152 recall = 0.560386 F-score = 0.700532 人名正确预测数：2965 预测为人名数：3174 测试集实际标注为人名数：5291），可见效果较差。而且迭代次数达到230多次。


## 二、文件使用说明

1.主文件夹中，exec.sh文件中为执行命令，trainData、testData、outputData和template文件分别为训练数据、测试数据、标注结果输出文件和模板文件。其中训练、测试数据以及结果为第5次交叉验证的数据。

2.SourceCode文件夹中语料处理源代码说明：

(1)实验环境：Ubuntu 14.04.5 LTS，512MB RAM, 2GB Disk

(2)编译环境：gcc version 4.8.5 (Ubuntu 4.8.5-2ubuntu1~14.04.1)

(3)编程语言：C++(100%)

(4)basicProcess.cc文件为运行主程序文件，所有处理方法都在methods.h文件中。


注意：
1.测试时，请把SourceCode文件夹中trainingData.txt替换为第二次作业的原始语料。把SourceCode文件夹中outputData文件替换为实际输出结果。

2.限于系统性能等因素，5-fold交叉验证没有一次进行，而是分别进行，具体可参考代码中注释。

3.上述所有文件都可以用普通文本编辑器打开。