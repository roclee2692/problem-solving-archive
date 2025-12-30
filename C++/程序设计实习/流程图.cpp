// 【教师科研工作量管理系统】
// ├── 登录与权限
// │   ├── 用户登录
// │   └── 角色分流（教师/管理员）
// ├── 教师端（普通用户）
// │   ├── 申报管理
// │   │   ├── 论文申报
// │   │   ├── 项目申报
// │   │   └── 经费申报
// │   └── 申报查询
// │       ├── 查看本人申报记录
// │       └── 查看审核结果/反馈
// ├── 管理员端（学校/管理员）
// │   ├── 基础信息管理
// │   │   ├── 学院信息（增删改查）
// │   │   └── 教师信息（增删改查）
// │   ├── 审核管理
// │   │   ├── 待审核列表
// │   │   ├── 审核通过/驳回
// │   │   └── 填写反馈意见
// │   └── 统计查询
// │       ├── 教师工作量统计
// │       └── 学院工作量统计
// └── 数据管理
//     ├── txt文件读取
//     └── txt文件保存

// =============================
// 【硬要求】两层
// =============================
// 【A. 题目专属功能（教师科研工作量系统）】
// • 教师申报：论文（级别/顺序）、项目（级别/顺序）、经费（经费计分）
// • 学校审核：核对类型和分数，反馈学院/教师
// • 学校+教师：学院/教师/项目 的增删改查 + 统计查询
// • 加分：申请、审核通过、分数统计（你本题本来就要求这些）

// 【B. 所有系统通用硬要求】
// • 菜单
// • 分用户：管理员/普通
// • 增删改查
// • txt 文件存储、可读历史
// • 申请 + 审核
// • 模块化（函数/多文件都行）
// • 上机跑通
// • 代码风格：锯齿型
// • 报告按模板
// • 90+：要“创意/独特算法”+ 全功能 + 文档 + 流程图 + 可靠性

// =============================
// 【图1：系统功能结构图】
// =============================
/*
```mermaid
graph TB
    System[教师科研工作量管理系统]
    
    System --> Login[登录认证模块]
    System --> Teacher[教师功能模块]
    System --> Admin[管理员功能模块]
    System --> Data[数据管理模块]
    System --> Rule[规则驱动计分模块]
    
    %% 登录认证
    Login --> L1[用户身份验证]
    Login --> L2[角色权限分配]
    L2 --> L2a[教师角色]
    L2 --> L2b[管理员角色]
    
    %% 教师功能
    Teacher --> T1[申报管理]
    Teacher --> T2[查询管理]
    
    T1 --> T1a[论文申报]
    T1 --> T1b[项目申报]
    T1 --> T1c[经费申报]
    
    T2 --> T2a[查看本人申报]
    T2 --> T2b[查看审核结果]
    
    %% 管理员功能
    Admin --> A1[基础信息管理]
    Admin --> A2[审核管理]
    Admin --> A3[统计分析]
    
    A1 --> A1a[学院管理]
    A1 --> A1b[教师管理]
    A1a --> A1a1[增加学院]
    A1a --> A1a2[删除学院]
    A1b --> A1b1[新增教师]
    
    A2 --> A2a[待审核列表]
    A2 --> A2b[审核决策]
    A2 --> A2c[填写反馈]
    A2b --> A2b1[通过申请]
    A2b --> A2b2[驳回申请]
    A2b --> A2b3[分数覆盖]
    
    A3 --> A3a[教师工作量排名]
    A3 --> A3b[学院工作量排名]
    
    %% 数据管理
    Data --> D1[文件读写]
    Data --> D2[数据持久化]
    
    D1 --> D1a[colleges.txt]
    D1 --> D1b[users.txt]
    D1 --> D1c[applies.txt]
    
    D2 --> D2a[手动保存s键]
    D2 --> D2b[退出自动保存]
    
    %% 规则驱动计分
    Rule --> R1[规则文件加载]
    Rule --> R2[动态计分]
    Rule --> R3[规则查询]
    
    R1 --> R1a[score_rules.txt]
    R2 --> R2a[论文计分算法]
    R2 --> R2b[项目计分算法]
    R2 --> R2c[经费计分算法]
    
    R3 --> R3a[级别分数查询]
    R3 --> R3b[顺序系数查询]
    
    style System fill:#e1f5ff
    style Login fill:#fff4e1
    style Teacher fill:#e8f5e9
    style Admin fill:#fce4ec
    style Data fill:#f3e5f5
    style Rule fill:#fff9c4
```
*/

// =============================
// 【图2：教师申报业务流程图】
// =============================
/*
```mermaid
flowchart TD
    Start([教师登录成功]) --> Menu[显示教师菜单]
    
    Menu --> Choice{选择操作}
    Choice --> |1| Paper[论文申报]
    Choice --> |2| Project[项目申报]
    Choice --> |3| Fund[经费申报]
    Choice --> |4| ViewMy[查看我的申报]
    Choice --> |5| ViewApproved[查看已通过申报]
    Choice --> |s| SaveManual[手动保存到文件]
    Choice --> |0| SaveAuto[自动保存并退出]
    
    %% 论文申报流程
    Paper --> InputP1[输入年份year]
    InputP1 --> InputP2[输入标题title]
    InputP2 --> InputP3[输入级别level<br/>national/provincial/school]
    InputP3 --> InputP4[输入作者顺序order]
    InputP4 --> GenerateP
    
    %% 项目申报流程
    Project --> InputJ1[输入年份year]
    InputJ1 --> InputJ2[输入标题title]
    InputJ2 --> InputJ3[输入级别level]
    InputJ3 --> InputJ4[输入负责人顺序order]
    InputJ4 --> GenerateJ
    
    %% 经费申报流程
    Fund --> InputF1[输入年份year]
    InputF1 --> InputF2[输入金额amount]
    InputF2 --> GenerateF
    
    GenerateP --> Generate[生成申报ID<br/>nextApplyId函数]
    GenerateJ --> Generate
    GenerateF --> Generate
    
    Generate --> SetStatus[初始化状态<br/>status=0待审核<br/>score=0]
    SetStatus --> SaveMem[写入内存<br/>applies.push_back]
    SaveMem --> ShowSuccess[显示提交成功<br/>返回申报ID]
    ShowSuccess --> Menu
    
    %% 查看功能
    ViewMy --> FilterMy[筛选uid=当前用户]
    FilterMy --> ShowTable1[表格展示申报列表]
    ShowTable1 --> Menu
    
    ViewApproved --> FilterApproved[筛选uid=当前用户<br/>且status=1已通过]
    FilterApproved --> ShowTable2[表格展示通过列表]
    ShowTable2 --> Menu
    
    %% 保存功能
    SaveManual --> CallSave1[调用saveAll函数]
    CallSave1 --> ShowSaved[显示Saved]
    ShowSaved --> Menu
    
    SaveAuto --> CallSave2[调用saveAll函数]
    CallSave2 --> Logout[退出登录]
    Logout --> End([结束])
    
    style Start fill:#e8f5e9
    style Generate fill:#fff9c4
    style SaveMem fill:#e1f5ff
    style End fill:#ffebee
```
*/

// =============================
// 【图3：管理员审核业务流程图】
// =============================
/*
```mermaid
flowchart TD
    Start([管理员登录成功]) --> Menu[显示管理员菜单]
    
    Menu --> Choice{选择操作}
    Choice --> |1-5| CRUD[基础信息管理]
    Choice --> |6| ShowAll[查看所有申报]
    Choice --> |7| ShowPending[查看待审核申报]
    Choice --> |8| Review[审核申报]
    Choice --> |9| StatsT[教师统计]
    Choice --> |10| StatsC[学院统计]
    Choice --> |s| Save[手动保存]
    Choice --> |0| Exit[退出登录]
    
    %% 审核流程
    ShowPending --> Filter[筛选status=0]
    Filter --> Display[表格展示待审核列表<br/>AID/类型/教师/年份/标题]
    Display --> InputAID[管理员输入申报ID]
    
    InputAID --> CheckExist{申报是否存在}
    CheckExist --> |否| NotFound[显示未找到]
    NotFound --> Menu
    
    CheckExist --> |是| CheckStatus{是否待审核}
    CheckStatus --> |已审核| AlreadyDone[显示已审核]
    AlreadyDone --> Menu
    
    CheckStatus --> |待审核| ShowDetail[显示申报详情<br/>类型/用户/标题/级别等]
    ShowDetail --> AutoCalc[系统自动计分<br/>调用calcScore函数]
    
    AutoCalc --> CallRule[规则驱动计分]
    CallRule --> |论文| RulePaper[查询paper规则<br/>基础分×顺序系数]
    CallRule --> |项目| RuleProject[查询project规则<br/>基础分×顺序系数]
    CallRule --> |经费| RuleFund[查询fund规则<br/>金额÷10000×费率]
    
    RulePaper --> ShowAuto
    RuleProject --> ShowAuto
    RuleFund --> ShowAuto
    
    ShowAuto[显示系统建议分数] --> Decision{管理员决策}
    
    Decision --> |1-通过| InputFB1[输入审核意见]
    Decision --> |2-驳回| InputFB2[输入驳回原因]
    Decision --> |其他| Invalid[显示无效输入]
    Invalid --> Menu
    
    InputFB1 --> OverrideScore{是否修改分数}
    OverrideScore --> |输入-1| UseAuto[使用系统建议分]
    OverrideScore --> |输入具体值| UseCustom[使用自定义分数]
    
    UseAuto --> Approve[设置status=1已通过<br/>保存分数和意见]
    UseCustom --> Approve
    
    InputFB2 --> Reject[设置status=2已驳回<br/>score=0<br/>保存驳回原因]
    
    Approve --> UpdateMem[更新内存数据<br/>applies向量]
    Reject --> UpdateMem
    
    UpdateMem --> SaveFile[保存到applies.txt]
    SaveFile --> ShowResult[显示审核完成]
    ShowResult --> Menu
    
    %% 统计功能
    StatsT --> CalcTeacher[按教师汇总<br/>论文/项目/经费分数]
    CalcTeacher --> SortT[按总分降序排序]
    SortT --> DisplayT[表格展示排名]
    DisplayT --> Menu
    
    StatsC --> CalcCollege[按学院汇总<br/>所属教师总分]
    CalcCollege --> SortC[按学院总分降序]
    SortC --> DisplayC[表格展示排名]
    DisplayC --> Menu
    
    CRUD --> Menu
    ShowAll --> Menu
    Save --> Menu
    Exit --> End([结束])
    
    style Start fill:#fce4ec
    style AutoCalc fill:#fff9c4
    style CallRule fill:#e1f5ff
    style UpdateMem fill:#f3e5f5
    style End fill:#ffebee
```
*/

// =============================
// 【需求分析】
// =============================
// 【系统目标】
// • 实现教师科研工作量：申报、审核、反馈、查询统计
// • 用 txt 持久化保存历史数据

// 【用户角色】
// • 管理员（学校）：信息管理、审核、统计
// • 普通用户（教师）：申报、查询结果

// 【功能需求（按模块）】
// 1) 登录与权限
// • 用户登录（账号/密码）
// • 按角色进入不同菜单（管理员/教师）

// 2) 教师端：科研申报
// • 论文申报（级别、顺序、标题、年份）
// • 项目申报（级别、顺序、标题、年份）
// • 经费申报（经费金额、年份）
// • 查看本人申报记录、审核结果、反馈

// 3) 管理员端：审核与反馈
// • 查看待审核列表
// • 审核通过/驳回
// • 校验申报类型与分数（自动计算/人工调整）
// • 填写反馈并保存

// 4) 基础信息管理（增删改查）
// • 学院信息 CRUD
// • 教师信息 CRUD
// • 申报记录查询/删除（可选改）

// 5) 统计查询（加分）
// • 按教师汇总已通过的总分（排序）
// • 按学院汇总总分（可选）

// 6) 数据持久化
// • 所有数据保存到 txt
// • 支持启动读取历史记录、退出保存

// 【非功能要求】
// • 菜单式交互、锯齿型格式
// • 模块化：函数/多文件
// • 上机可运行、截图可证明