/********************************************************************************
** Form generated from reading UI file 'GuiPreferencesDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIPREFERENCESDIALOG_H
#define UI_GUIPREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GuiPreferencesDialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QCheckBox *timingMarkersCheck;
    QLabel *label;
    QComboBox *followStopPointCombo;
    QSpacerItem *horizontalSpacer;
    QCheckBox *showNoteNamesCheck;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *courtesyAccidentalsCheck;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QCheckBox *showTutorPagesCheck;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2x;
    QLabel *label_2;
    QComboBox *videoOptimiseCombo;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GuiPreferencesDialog)
    {
        if (GuiPreferencesDialog->objectName().isEmpty())
            GuiPreferencesDialog->setObjectName(QString::fromUtf8("GuiPreferencesDialog"));
        GuiPreferencesDialog->resize(339, 331);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GuiPreferencesDialog->sizePolicy().hasHeightForWidth());
        GuiPreferencesDialog->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(GuiPreferencesDialog);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox_2 = new QGroupBox(GuiPreferencesDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        timingMarkersCheck = new QCheckBox(groupBox_2);
        timingMarkersCheck->setObjectName(QString::fromUtf8("timingMarkersCheck"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(timingMarkersCheck->sizePolicy().hasHeightForWidth());
        timingMarkersCheck->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(timingMarkersCheck, 2, 0, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        followStopPointCombo = new QComboBox(groupBox_2);
        followStopPointCombo->setObjectName(QString::fromUtf8("followStopPointCombo"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(followStopPointCombo->sizePolicy().hasHeightForWidth());
        followStopPointCombo->setSizePolicy(sizePolicy2);
        followStopPointCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout->addWidget(followStopPointCombo, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 1, 1);

        showNoteNamesCheck = new QCheckBox(groupBox_2);
        showNoteNamesCheck->setObjectName(QString::fromUtf8("showNoteNamesCheck"));

        gridLayout->addWidget(showNoteNamesCheck, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        courtesyAccidentalsCheck = new QCheckBox(groupBox_2);
        courtesyAccidentalsCheck->setObjectName(QString::fromUtf8("courtesyAccidentalsCheck"));

        gridLayout->addWidget(courtesyAccidentalsCheck, 1, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(GuiPreferencesDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(0);
        showTutorPagesCheck = new QCheckBox(groupBox_3);
        showTutorPagesCheck->setObjectName(QString::fromUtf8("showTutorPagesCheck"));

        gridLayout_2->addWidget(showTutorPagesCheck, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox = new QGroupBox(GuiPreferencesDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout_2x = new QGridLayout();
        gridLayout_2x->setObjectName(QString::fromUtf8("gridLayout_2x"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2x->addWidget(label_2, 0, 0, 1, 1);

        videoOptimiseCombo = new QComboBox(groupBox);
        videoOptimiseCombo->setObjectName(QString::fromUtf8("videoOptimiseCombo"));
        videoOptimiseCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_2x->addWidget(videoOptimiseCombo, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2x);


        verticalLayout_4->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(GuiPreferencesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);


        retranslateUi(GuiPreferencesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GuiPreferencesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GuiPreferencesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GuiPreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *GuiPreferencesDialog)
    {
        GuiPreferencesDialog->setWindowTitle(QApplication::translate("GuiPreferencesDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GuiPreferencesDialog", "Score Settings", 0, QApplication::UnicodeUTF8));
        timingMarkersCheck->setText(QApplication::translate("GuiPreferencesDialog", "Timing Markers", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GuiPreferencesDialog", "Follow stop point:", 0, QApplication::UnicodeUTF8));
        showNoteNamesCheck->setText(QApplication::translate("GuiPreferencesDialog", "Show Note Names", 0, QApplication::UnicodeUTF8));
        courtesyAccidentalsCheck->setText(QApplication::translate("GuiPreferencesDialog", "Courtesy Accidentals", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("GuiPreferencesDialog", "Music Course", 0, QApplication::UnicodeUTF8));
        showTutorPagesCheck->setText(QApplication::translate("GuiPreferencesDialog", "Show Tutor Help Pages", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("GuiPreferencesDialog", "Video  Settings", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GuiPreferencesDialog", "Video optimisation:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GuiPreferencesDialog: public Ui_GuiPreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIPREFERENCESDIALOG_H
