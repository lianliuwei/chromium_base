# 波形显示控件设计

## 对象结构

分为视图层（view）和逻辑层（ui），用户使用ui层的接口，不显式操作view。view层负责波形的绘制，ui层维护波形控件的逻辑结构，可以用代码配置相关界面。
这样的好处是：

- view可以重复创建，创建的时候只需要拉取ui层的信息。
- 退出时候view可以先关闭，而ui层可以等待依赖的上层退出才退出
- 显示和逻辑分离

## 主要对象
- Wave
- OscWave
- SimpleAnaWave
- SimpleDigitWave
- WaveViewFactory
- WaveView
- WaveContainer
- MeasureLine
- SingleLine
- DualLine

## 生命周期

- Wave生命周期由Container控制
- Wave生命周期可以交给对应的WaveView对象控制
- Wave通知自己要被删除的消息，对应的delegate可以在这时候放弃对Wave的引用
- delegate可以设置Wave为无效状态，这时候Wave不应该调用delegate相关的接口，（用于Drag&Drop相关的情况，这时候需要有Wave存在）
- MeasureLine 生命周期类似于Wave

## 显示对象创建

不同的扩展需要不同的view类，用来对应不同的界面效果。需要定制Wave对应的WaveView，使用工厂方法来实现动态绑定。

## 测量线

测量线属于WaveContainer，可以选择对应的WaveView，这样可以实整体测量。

## 数据接口
OscWave 需要导出所有位置属性相关的修改，因为需要设置到硬件中。还需要导出Trigger的位置。

SimpleAnaWave 和 SimpleDigitWave 不需要通知位置变化，只要设置相关的数据。显示由用户自由配置。

## 扩展
用于波形和示波器波形显示实现

### WaveContainer扩展
使用继承, WaveContainer没有规定对应的View接口， 方便子类使用自己合适的接口。

### Wave扩展
使用SupportsUserData方法扩展（chrome 中 WebContents 方法）
不能用继承的方法来扩展接口，这样需要暴露子类，但是如果不使用static_cast<> 强制转换，非常麻烦，需要修改WaveViewFactory， Wave中的子类和RTTI接口。而一般的情况，只是需要添加一些附加的属性。并不需要更改原来的操作接口。

如果需要不同的操作接口，请添加到相应的类信息到Wave和WaveViewFactory中。或者复制代码并更改，原来的架构已经不合适。

## 通知接口
波形控件，主要是显示波形，和由界面更改显示相关的配置。代码操作相关的配置的情况也是存在的。

数据更新，提供由ui层向view层通知数据变化的接口。

属性，提供一个通用的ui层向view层通知变化的接口，方便不同的Wave对象向对应的WaveView提供相关的消息通知。
  
	PropertyChanged(int id);

，而Wave向下设置的接口，则由子类自定义。
	

## 右键菜单
导出相关的MenuModel，界面可以添加自己的选项上去。

## toolbar

## 窗口管理
波形显示控件中的子窗口，显示几个，波形分配到哪个窗口，由View自行决定，UI给出相关的类型选择。但是UI逻辑上是没有相关窗口对象，降低复杂度。