"""
    Class Widgets Auto Update
    Class Widgets 自动更新
    Detrital
    Github Repositories https://github.com/Detritalw/CW-AutoUpdate
"""
from PyQt5 import uic
from loguru import logger
from datetime import datetime
from .ClassWidgets.base import PluginBase, SettingsBase, PluginConfig  # 导入CW的基类

from PyQt5.QtWidgets import QHBoxLayout, QPushButton, QFileDialog, QLineEdit
from qfluentwidgets import ImageLabel
import subprocess

class Plugin(PluginBase):  # 插件类
    def __init__(self, cw_contexts, method):  # 初始化
        super().__init__(cw_contexts, method)  # 调用父类初始化方法

        self.cfg = PluginConfig(self.PATH, 'config.json')  # 实例化配置类

    def execute(self):  # 自启动执行部分

        logger.success('Plugin1 executed!')
        logger.info(f'Config path: {self.PATH}')

    def update(self, cw_contexts):  # 自动更新部分
        super().update(cw_contexts)  # 调用父类更新方法
        self.cfg.update_config()  # 更新配置

        if self.method.is_get_notification():
            logger.warning('warning', f'Plugin1 got notification! Title: {self.cw_contexts["Notification"]["title"]}')

            if self.cw_contexts['Notification']['state'] == 0:  # 如果下课
                self.method.subprocess_exec(self.cfg['name'], self.cfg['action'])  # 调用CW方法构建自动化


# 设置页
class Settings(SettingsBase):
    def __init__(self, plugin_path, parent=None):
        super().__init__(plugin_path, parent)
        uic.loadUi(f'{self.PATH}/settings.ui', self)  # 加载设置界面

        # 添加打开转换器按钮
        self.openButton = self.findChild(QPushButton, 'openButton')
        self.openButton.clicked.connect(self.open_converter)

        # 添加新的控件
        self.filePathEdit = self.findChild(QLineEdit, 'filePathEdit')
        self.selectFileButton = self.findChild(QPushButton, 'selectFileButton')
        self.selectFileButton.clicked.connect(self.select_file)

        self.convertButton = self.findChild(QPushButton, 'convertButton')
        self.convertButton.clicked.connect(self.convert_csv_to_json)

        self.helpButton = self.findChild(QPushButton, 'helpButton')
        self.helpButton.clicked.connect(self.open_help)

    def open_converter(self):
        subprocess.Popen([f'{self.PATH}/cw-CSV-import.exe'])
        logger.info('打开转换器')

    def select_file(self):
        file_path, _ = QFileDialog.getOpenFileName(self, "选择文件", "", "All Files (*)")
        if file_path:
            self.filePathEdit.setText(file_path)
            logger.info(f'选择的文件: {file_path}')

    def convert_csv_to_json(self):
        subprocess.Popen([f'{self.PATH}/csv2json.exe'])
        logger.info('从csv文件转换到json课表文件')

    def open_help(self):
        subprocess.Popen([f'{self.PATH}/help.exe'])
        logger.info('需要帮助')
