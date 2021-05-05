#需解决的问题
1、RPC描述怎么给Lua层调用（调用方式的问题）
解决办法:导出lua远程调用的桩代码，提供rpc.so库给lua层调用

2、CRpc以什么形式暴露给其他外部接入?
解决办法:通过定义app,在app类里定义好了CRpc,外部程序通过继承实现app的实例

3、怎么实现协程

<<<<<<< Updated upstream
4、在so里怎么访问app里的rpc接口
=======

4、在so里怎么访问app里的rpc数据
现在问题是so里的rpc实例还没初始化

5、连接管理实现

6、缓冲区实现
>>>>>>> Stashed changes

