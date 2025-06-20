import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms
from sklearn.model_selection import train_test_split
import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE
from tqdm import tqdm  # 导入tqdm用于进度条显示

# 设置随机种子，确保实验结果可复现
torch.manual_seed(42)
np.random.seed(42)

# 检查CUDA是否可用，选择设备（GPU或CPU）
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
# device = 'cpu' # 强制使用CPU
print(f"使用设备: {device}")  # 输出使用的设备类型

# -----------------------------
# 1. 数据准备（训练集和验证集）
# -----------------------------

# 定义数据预处理：将图像转换为张量并进行归一化
transform = transforms.Compose([
    transforms.ToTensor(),  # 将图像转换为张量，像素值从[0,255]变为[0,1]
    transforms.Normalize((0.5,), (0.5,))  # 归一化到[-1,1]，公式：(x - mean) / std
])

# 加载MNIST数据集
train_dataset = datasets.MNIST(root='./data', train=True, transform=transform, download=True)  # 下载并加载训练集
test_dataset = datasets.MNIST(root='./data', train=False, transform=transform, download=True)  # 下载并加载测试集

# 提取训练集的图像和标签为numpy数组，以便分割
x_train_full = train_dataset.data.numpy()  # 训练集图像数据，形状为(60000, 28, 28)
y_train_full = train_dataset.targets.numpy()  # 训练集标签，形状为(60000,)

# 将训练集分割为训练集和验证集，验证集比例20%
x_train, x_val, y_train, y_val = train_test_split(
    x_train_full, y_train_full, test_size=0.2, random_state=42
)  # test_size=0.2表示20%为验证集，剩余80%为训练集

# 将分割后的数据转换回PyTorch张量
x_train = torch.from_numpy(x_train).float().unsqueeze(1) / 255.0  # 增加通道维度，归一化到[0,1]
x_val = torch.from_numpy(x_val).float().unsqueeze(1) / 255.0  # 同上，验证集数据
y_train = torch.from_numpy(y_train).long()  # 转换为长整型张量（标签）
y_val = torch.from_numpy(y_val).long()  # 同上，验证集标签

# 测试集数据预处理
x_test = test_dataset.data.float().unsqueeze(1) / 255.0  # 测试集图像，增加通道维度并归一化
y_test = test_dataset.targets.long()  # 测试集标签，转换为长整型张量

# 创建数据加载器，方便批量处理
train_loader = torch.utils.data.DataLoader(
    list(zip(x_train, y_train)), batch_size=64, shuffle=True
)  # 训练集加载器，批量大小64，打乱数据
val_loader = torch.utils.data.DataLoader(
    list(zip(x_val, y_val)), batch_size=64, shuffle=False
)  # 验证集加载器，批量大小64，不打乱数据
test_loader = torch.utils.data.DataLoader(
    list(zip(x_test, y_test)), batch_size=64, shuffle=False
)  # 测试集加载器，批量大小64，不打乱数据


# -----------------------------
# 2. 构建网络
# -----------------------------

class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Conv2d(1, 32, kernel_size=3, padding=1)  # 卷积层1：输入1通道，输出32通道，3x3卷积核
        self.pool = nn.MaxPool2d(2, 2)  # 池化层：2x2最大池化，减少维度
        self.conv2 = nn.Conv2d(32, 64, kernel_size=3, padding=1)  # 卷积层2：输入32通道，输出64通道
        self.fc1 = nn.Linear(64 * 7 * 7, 128)  # 全连接层1：输入64*7*7，输出128
        self.fc2 = nn.Linear(128, 10)  # 输出层：输入128，输出10（对应10个类别）

    def forward(self, x):
        x = self.pool(torch.relu(self.conv1(x)))  # 卷积1 + ReLU激活 + 池化
        x = self.pool(torch.relu(self.conv2(x)))  # 卷积2 + ReLU激活 + 池化
        x = x.view(-1, 64 * 7 * 7)  # 展平特征图为1维向量
        x = torch.relu(self.fc1(x))  # 全连接层1 + ReLU激活
        x = self.fc2(x)  # 输出层，生成10个类别的logits
        return x


# 实例化模型并移动到GPU（如果可用）
model = CNN().to(device)  # 将模型移到指定设备（GPU或CPU）

# -----------------------------
# 3. 训练
# -----------------------------

# 定义损失函数和优化器
criterion = nn.CrossEntropyLoss()  # 交叉熵损失函数，用于分类任务
optimizer = optim.Adam(model.parameters(), lr=0.001)  # Adam优化器，学习率为0.001

# 初始化记录训练和验证的损失及准确率
num_epochs = 100  # 训练轮数
train_losses, val_losses = [], []  # 存储每个epoch的损失
train_accuracies, val_accuracies = [], []  # 存储每个epoch的准确率

# 训练循环
for epoch in range(num_epochs):
    model.train()  # 设置模型为训练模式
    running_loss = 0.0  # 累计训练损失
    correct = 0  # 正确预测的样本数
    total = 0  # 总样本数
    train_bar = tqdm(train_loader, desc=f"Epoch {epoch + 1}/{num_epochs}")  # 创建训练进度条
    for data, target in train_bar:
        data, target = data.to(device), target.to(device)  # 将数据和标签移到GPU
        optimizer.zero_grad()  # 清零梯度
        output = model(data)  # 前向传播，得到预测结果
        loss = criterion(output, target)  # 计算损失
        loss.backward()  # 反向传播，计算梯度
        optimizer.step()  # 更新模型参数

        running_loss += loss.item()  # 累加损失值
        _, predicted = torch.max(output.data, 1)  # 获取预测类别
        total += target.size(0)  # 累加样本数
        correct += (predicted == target).sum().item()  # 累加正确预测数

        # 更新进度条显示当前损失和准确率
        train_bar.set_postfix(loss=loss.item(), accuracy=correct / total)

    train_loss = running_loss / len(train_loader)  # 平均训练损失
    train_accuracy = correct / total  # 训练准确率
    train_losses.append(train_loss)  # 记录训练损失
    train_accuracies.append(train_accuracy)  # 记录训练准确率
    print(f"Epoch {epoch + 1}/{num_epochs}, Train Loss: {train_loss:.4f}, Train Accuracy: {train_accuracy:.4f}")

    # 验证阶段
    model.eval()  # 设置模型为评估模式
    val_loss = 0.0  # 累计验证损失
    correct = 0  # 正确预测的样本数
    total = 0  # 总样本数
    with torch.no_grad():  # 禁用梯度计算，节省内存
        for data, target in val_loader:
            data, target = data.to(device), target.to(device)  # 将数据和标签移到GPU
            output = model(data)  # 前向传播
            loss = criterion(output, target)  # 计算损失
            val_loss += loss.item()  # 累加损失值
            _, predicted = torch.max(output.data, 1)  # 获取预测类别
            total += target.size(0)  # 累加样本数
            correct += (predicted == target).sum().item()  # 累加正确预测数
    val_loss /= len(val_loader)  # 平均验证损失
    val_accuracy = correct / total  # 验证准确率
    val_losses.append(val_loss)  # 记录验证损失
    val_accuracies.append(val_accuracy)  # 记录验证准确率
    print(f"Epoch {epoch + 1}/{num_epochs}, Val Loss: {val_loss:.4f}, Val Accuracy: {val_accuracy:.4f}")

# -----------------------------
# 4. 测试
# -----------------------------

# 测试模型性能
model.eval()  # 设置模型为评估模式
test_loss = 0.0  # 累计测试损失
correct = 0  # 正确预测的样本数
total = 0  # 总样本数
test_bar = tqdm(test_loader, desc="Testing")  # 创建测试进度条
with torch.no_grad():  # 禁用梯度计算
    for data, target in test_bar:
        data, target = data.to(device), target.to(device)  # 将数据和标签移到GPU
        output = model(data)  # 前向传播
        loss = criterion(output, target)  # 计算损失
        test_loss += loss.item()  # 累加损失值
        _, predicted = torch.max(output.data, 1)  # 获取预测类别
        total += target.size(0)  # 累加样本数
        correct += (predicted == target).sum().item()  # 累加正确预测数

        # 更新进度条显示当前准确率
        test_bar.set_postfix(accuracy=correct / total)

test_loss /= len(test_loader)  # 平均测试损失
test_accuracy = correct / total  # 测试准确率
print(f"Test Loss: {test_loss:.4f}, Test Accuracy: {test_accuracy:.4f}")

# -----------------------------
# 5. 可视化
# -----------------------------

# 5.1 绘制准确率和损失函数曲线
plt.figure(figsize=(12, 4))  # 设置画布大小
plt.subplot(1, 2, 1)  # 创建1x2子图的第一个
plt.plot(train_losses, label='Train Loss')  # 绘制训练损失曲线
plt.plot(val_losses, label='Val Loss')  # 绘制验证损失曲线
plt.xlabel('Epoch')  # x轴标签
plt.ylabel('Loss')  # y轴标签
plt.legend()  # 显示图例
plt.title('Loss Curve')  # 图标题

plt.subplot(1, 2, 2)  # 创建1x2子图的第二个
plt.plot(train_accuracies, label='Train Accuracy')  # 绘制训练准确率曲线
plt.plot(val_accuracies, label='Val Accuracy')  # 绘制验证准确率曲线
plt.xlabel('Epoch')  # x轴标签
plt.ylabel('Accuracy')  # y轴标签
plt.legend()  # 显示图例
plt.title('Accuracy Curve')  # 图标题
plt.show()  # 显示图像

# 5.2 PCA和t-SNE降维可视化
# 提取模型输出特征（softmax前的logits）
model.eval()  # 设置模型为评估模式
features = []  # 存储模型输出特征
labels = []  # 存储对应标签
with torch.no_grad():
    for data, target in test_loader:
        data = data.to(device)  # 将数据移到GPU
        output = model(data)  # 获取模型输出
        features.append(output.cpu().numpy())  # 转换为numpy数组并移回CPU
        labels.append(target.numpy())  # 存储标签
features = np.concatenate(features, axis=0)  # 合并所有批次的特征
labels = np.concatenate(labels, axis=0)  # 合并所有批次的标签

# 展平原始测试集图像
x_test_flat = x_test.view(x_test.size(0), -1).numpy()  # 将图像展平为(10000, 784)

# PCA降维
pca = PCA(n_components=2)  # PCA降维到2维
pca_raw = pca.fit_transform(x_test_flat)  # 对原始图像进行PCA降维
pca_features = pca.fit_transform(features)  # 对模型特征进行PCA降维

# t-SNE降维（为加速计算，仅使用前1000个样本）
tsne = TSNE(n_components=2, random_state=42)  # t-SNE降维到2维
tsne_raw = tsne.fit_transform(x_test_flat[:1000])  # 对原始图像降维
tsne_features = tsne.fit_transform(features[:1000])  # 对模型特征降维

# 绘制PCA和t-SNE散点图
plt.figure(figsize=(12, 8))  # 设置画布大小
plt.subplot(2, 2, 1)  # 创建2x2子图的第一个
plt.scatter(pca_raw[:, 0], pca_raw[:, 1], c=labels, cmap='tab10', s=5)  # 绘制原始图像PCA散点图
plt.title('PCA of Raw Images')  # 图标题

plt.subplot(2, 2, 2)  # 创建2x2子图的第二个
plt.scatter(pca_features[:, 0], pca_features[:, 1], c=labels, cmap='tab10', s=5)  # 绘制模型特征PCA散点图
plt.title('PCA of Model Features')  # 图标题

plt.subplot(2, 2, 3)  # 创建2x2子图的第三个
plt.scatter(tsne_raw[:, 0], tsne_raw[:, 1], c=labels[:1000], cmap='tab10', s=5)  # 绘制原始图像t-SNE散点图
plt.title('t-SNE of Raw Images')  # 图标题

plt.subplot(2, 2, 4)  # 创建2x2子图的第四个
plt.scatter(tsne_features[:, 0], tsne_features[:, 1], c=labels[:1000], cmap='tab10', s=5)  # 绘制模型特征t-SNE散点图
plt.title('t-SNE of Model Features')  # 图标题
plt.show()  # 显示图像