# localization-tool-for-Men-of-War
这是一个用于帮助进行战争之人游戏本地化工作的小程序

目前全部功能仅支持CTA以前的战争之人(MOW)游戏！CTA更换了本地化文件格式。

目前施工情况：
一·本地化文件创建工具
用于从0创建或者修改MOW系列游戏的lng/inc类本地化文件

 1.从resource文件夹结构创建本地化文件
    -在设置中选择resource文件夹路径，然后可以自动创建四种类别(单位/兵种/武器/物品)的本地化文件。
    -通过树状列表编辑本地化文本
    注1：该功能尚在开发中，也许未来ParaTranz能执行所有需要的功能时该工具会被废弃。
    
二·lng/csv转换工具
用于将MOW支持的lng/inc文件与在线翻译平台Paratranz支持的csv格式相互转换，并提供一些必要的方便功能。

 1.将原文导入csv
    -从lng文件生成csv文件，lng内的本地化文本作为原文，译文留空
    -从csv文件生成csv文件，只是单纯的将csv文件导入软件
    注1：从lng生成时将会保留除\"外所有的转义序列，但是\"会被替换成csv能识别的""。
    注2：文件编码Windows1251=俄文编码，如果你发现导入的文本出现乱码，尝试切换编码。暂时只额外支持俄文，其它语种以后加入
    
 2.将翻译导入csv
    -从lng文件生成翻译   ，lng内的本地化文本作为译文
    -从csv文件生成翻译   ，将csv内匹配key的译文转移到新文件
    注1：必须存在导入的原文才能使用该功能。
    注2：尽量不要向单个文件重复使用该功能，我并未测试过反复导入会产生什么后果。
    注3：如果本来的文件中已经包含了译文，目前默认新译文将会覆盖旧译文。
    
 3.将翻译导入lng
    尚在施工中
