/********************************************************************************
** Form generated from reading UI file 'editorPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORPAGE_H
#define UI_EDITORPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesEditorPage
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *fontCheckBox;
    QPushButton *fontSelectionButton;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSlider *gridWidthSlider;
    QCheckBox *activateAlignmentCheckBox;
    QLabel *label_20;
    QCheckBox *activateGridCheckBox;
    QLabel *label_13;
    QCheckBox *showGridCheckBox;
    QCheckBox *showAlignmentCheckBox;
    QSlider *indexGridSlider;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_14;
    QFrame *frame_7;
    QGridLayout *gridLayout_3;
    QSlider *dragAreaSizeSlider;
    QLabel *label_15;
    QFrame *frame_6;
    QSlider *horizontalSlider;
    QLabel *label_9;
    QFrame *frame_4;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer;
    QComboBox *lineMode;
    QLabel *label_10;
    QLabel *label_11;
    QSlider *loopEdgeBoundsIndent;
    QLabel *label_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QSlider *embeddedLinkerSizeSlider;
    QSlider *embeddedLinkerIndentSlider;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_12;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *enableMoveLabelsCheckBox;
    QCheckBox *enableResizeLabelsCheckBox;
    QLabel *labelDistanceLabel;
    QSlider *labelDistanceSlider;
    QLabel *label_8;
    QFrame *frame_9;
    QGridLayout *gridLayout_7;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *paletteComboBox;
    QSpinBox *paletteSpinBox;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *PreferencesEditorPage)
    {
        if (PreferencesEditorPage->objectName().isEmpty())
            PreferencesEditorPage->setObjectName(QStringLiteral("PreferencesEditorPage"));
        PreferencesEditorPage->resize(500, 638);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesEditorPage->sizePolicy().hasHeightForWidth());
        PreferencesEditorPage->setSizePolicy(sizePolicy);
        PreferencesEditorPage->setMinimumSize(QSize(50, 50));
        PreferencesEditorPage->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(PreferencesEditorPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(PreferencesEditorPage);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 480, 782));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_2->addWidget(label_5);

        frame_3 = new QFrame(scrollAreaWidgetContents);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
        frame_3->setMinimumSize(QSize(0, 40));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fontCheckBox = new QCheckBox(frame_3);
        fontCheckBox->setObjectName(QStringLiteral("fontCheckBox"));
        fontCheckBox->setEnabled(true);
        sizePolicy1.setHeightForWidth(fontCheckBox->sizePolicy().hasHeightForWidth());
        fontCheckBox->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(fontCheckBox);

        fontSelectionButton = new QPushButton(frame_3);
        fontSelectionButton->setObjectName(QStringLiteral("fontSelectionButton"));
        sizePolicy1.setHeightForWidth(fontSelectionButton->sizePolicy().hasHeightForWidth());
        fontSelectionButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(fontSelectionButton);


        verticalLayout_2->addWidget(frame_3);

        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridWidthSlider = new QSlider(frame);
        gridWidthSlider->setObjectName(QStringLiteral("gridWidthSlider"));
        sizePolicy.setHeightForWidth(gridWidthSlider->sizePolicy().hasHeightForWidth());
        gridWidthSlider->setSizePolicy(sizePolicy);
        gridWidthSlider->setMinimum(3);
        gridWidthSlider->setMaximum(150);
        gridWidthSlider->setSingleStep(1);
        gridWidthSlider->setPageStep(10);
        gridWidthSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(gridWidthSlider, 7, 1, 1, 2);

        activateAlignmentCheckBox = new QCheckBox(frame);
        activateAlignmentCheckBox->setObjectName(QStringLiteral("activateAlignmentCheckBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(activateAlignmentCheckBox->sizePolicy().hasHeightForWidth());
        activateAlignmentCheckBox->setSizePolicy(sizePolicy2);
        activateAlignmentCheckBox->setChecked(true);

        gridLayout->addWidget(activateAlignmentCheckBox, 4, 0, 1, 1);

        label_20 = new QLabel(frame);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout->addWidget(label_20, 8, 0, 1, 1);

        activateGridCheckBox = new QCheckBox(frame);
        activateGridCheckBox->setObjectName(QStringLiteral("activateGridCheckBox"));
        sizePolicy2.setHeightForWidth(activateGridCheckBox->sizePolicy().hasHeightForWidth());
        activateGridCheckBox->setSizePolicy(sizePolicy2);
        activateGridCheckBox->setTristate(false);

        gridLayout->addWidget(activateGridCheckBox, 2, 0, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 7, 0, 1, 1);

        showGridCheckBox = new QCheckBox(frame);
        showGridCheckBox->setObjectName(QStringLiteral("showGridCheckBox"));
        showGridCheckBox->setChecked(true);

        gridLayout->addWidget(showGridCheckBox, 1, 0, 1, 1);

        showAlignmentCheckBox = new QCheckBox(frame);
        showAlignmentCheckBox->setObjectName(QStringLiteral("showAlignmentCheckBox"));
        showAlignmentCheckBox->setMinimumSize(QSize(130, 0));
        showAlignmentCheckBox->setChecked(true);

        gridLayout->addWidget(showAlignmentCheckBox, 3, 0, 1, 1);

        indexGridSlider = new QSlider(frame);
        indexGridSlider->setObjectName(QStringLiteral("indexGridSlider"));
        sizePolicy.setHeightForWidth(indexGridSlider->sizePolicy().hasHeightForWidth());
        indexGridSlider->setSizePolicy(sizePolicy);
        indexGridSlider->setMinimum(5);
        indexGridSlider->setMaximum(150);
        indexGridSlider->setSingleStep(1);
        indexGridSlider->setPageStep(10);
        indexGridSlider->setValue(50);
        indexGridSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(indexGridSlider, 8, 1, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 1, 1, 1);


        verticalLayout_2->addWidget(frame);

        label_14 = new QLabel(scrollAreaWidgetContents);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_2->addWidget(label_14);

        frame_7 = new QFrame(scrollAreaWidgetContents);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_7);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        dragAreaSizeSlider = new QSlider(frame_7);
        dragAreaSizeSlider->setObjectName(QStringLiteral("dragAreaSizeSlider"));
        dragAreaSizeSlider->setMinimum(4);
        dragAreaSizeSlider->setMaximum(20);
        dragAreaSizeSlider->setValue(12);
        dragAreaSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(dragAreaSizeSlider, 0, 1, 1, 1);

        label_15 = new QLabel(frame_7);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_3->addWidget(label_15, 0, 0, 1, 1);


        verticalLayout_2->addWidget(frame_7);

        frame_6 = new QFrame(scrollAreaWidgetContents);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalSlider = new QSlider(frame_6);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(70, 0, 160, 21));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(frame_6, 0, Qt::AlignLeft);

        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_2->addWidget(label_9);

        frame_4 = new QFrame(scrollAreaWidgetContents);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(30);
        sizePolicy3.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy3);
        frame_4->setMinimumSize(QSize(50, 60));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_4);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 2, 1, 1);

        lineMode = new QComboBox(frame_4);
        lineMode->setObjectName(QStringLiteral("lineMode"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineMode->sizePolicy().hasHeightForWidth());
        lineMode->setSizePolicy(sizePolicy4);
        lineMode->setMinimumSize(QSize(0, 20));

        gridLayout_5->addWidget(lineMode, 0, 1, 1, 1);

        label_10 = new QLabel(frame_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 0, 0, 1, 1);

        label_11 = new QLabel(frame_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_11, 1, 0, 1, 1);

        loopEdgeBoundsIndent = new QSlider(frame_4);
        loopEdgeBoundsIndent->setObjectName(QStringLiteral("loopEdgeBoundsIndent"));
        sizePolicy.setHeightForWidth(loopEdgeBoundsIndent->sizePolicy().hasHeightForWidth());
        loopEdgeBoundsIndent->setSizePolicy(sizePolicy);
        loopEdgeBoundsIndent->setMinimum(1);
        loopEdgeBoundsIndent->setMaximum(15);
        loopEdgeBoundsIndent->setSingleStep(2);
        loopEdgeBoundsIndent->setPageStep(2);
        loopEdgeBoundsIndent->setValue(2);
        loopEdgeBoundsIndent->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(loopEdgeBoundsIndent, 1, 1, 1, 2);


        verticalLayout_2->addWidget(frame_4);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        embeddedLinkerSizeSlider = new QSlider(frame_2);
        embeddedLinkerSizeSlider->setObjectName(QStringLiteral("embeddedLinkerSizeSlider"));
        embeddedLinkerSizeSlider->setMinimum(4);
        embeddedLinkerSizeSlider->setMaximum(20);
        embeddedLinkerSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(embeddedLinkerSizeSlider, 0, 1, 1, 1);

        embeddedLinkerIndentSlider = new QSlider(frame_2);
        embeddedLinkerIndentSlider->setObjectName(QStringLiteral("embeddedLinkerIndentSlider"));
        embeddedLinkerIndentSlider->setMinimum(5);
        embeddedLinkerIndentSlider->setMaximum(20);
        embeddedLinkerIndentSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(embeddedLinkerIndentSlider, 1, 1, 1, 1);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);


        verticalLayout_2->addWidget(frame_2);

        label_12 = new QLabel(scrollAreaWidgetContents);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_2->addWidget(label_12);

        frame_5 = new QFrame(scrollAreaWidgetContents);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_5);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        enableMoveLabelsCheckBox = new QCheckBox(frame_5);
        enableMoveLabelsCheckBox->setObjectName(QStringLiteral("enableMoveLabelsCheckBox"));
        enableMoveLabelsCheckBox->setChecked(true);

        verticalLayout_3->addWidget(enableMoveLabelsCheckBox);

        enableResizeLabelsCheckBox = new QCheckBox(frame_5);
        enableResizeLabelsCheckBox->setObjectName(QStringLiteral("enableResizeLabelsCheckBox"));
        enableResizeLabelsCheckBox->setChecked(true);

        verticalLayout_3->addWidget(enableResizeLabelsCheckBox);

        labelDistanceLabel = new QLabel(frame_5);
        labelDistanceLabel->setObjectName(QStringLiteral("labelDistanceLabel"));

        verticalLayout_3->addWidget(labelDistanceLabel);

        labelDistanceSlider = new QSlider(frame_5);
        labelDistanceSlider->setObjectName(QStringLiteral("labelDistanceSlider"));
        labelDistanceSlider->setMaximum(500);
        labelDistanceSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(labelDistanceSlider);


        verticalLayout_2->addWidget(frame_5);

        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_2->addWidget(label_8);

        frame_9 = new QFrame(scrollAreaWidgetContents);
        frame_9->setObjectName(QStringLiteral("frame_9"));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(frame_9);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_6 = new QLabel(frame_9);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_7->addWidget(label_6, 0, 0, 1, 1);

        label_7 = new QLabel(frame_9);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_7->addWidget(label_7, 1, 0, 1, 1);

        paletteComboBox = new QComboBox(frame_9);
        paletteComboBox->setObjectName(QStringLiteral("paletteComboBox"));
        paletteComboBox->setLayoutDirection(Qt::LeftToRight);
        paletteComboBox->setEditable(false);
        paletteComboBox->setFrame(true);

        gridLayout_7->addWidget(paletteComboBox, 0, 1, 1, 1);

        paletteSpinBox = new QSpinBox(frame_9);
        paletteSpinBox->setObjectName(QStringLiteral("paletteSpinBox"));
        paletteSpinBox->setMinimum(1);
        paletteSpinBox->setMaximum(5);

        gridLayout_7->addWidget(paletteSpinBox, 1, 1, 1, 1);


        verticalLayout_2->addWidget(frame_9);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(PreferencesEditorPage);

        paletteComboBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PreferencesEditorPage);
    } // setupUi

    void retranslateUi(QWidget *PreferencesEditorPage)
    {
        label_5->setText(QApplication::translate("PreferencesEditorPage", "Font", 0));
        fontCheckBox->setText(QApplication::translate("PreferencesEditorPage", "Use some of system fonts", 0));
        fontSelectionButton->setText(QApplication::translate("PreferencesEditorPage", "Choose Font", 0));
        label->setText(QApplication::translate("PreferencesEditorPage", "Grid", 0));
        activateAlignmentCheckBox->setText(QApplication::translate("PreferencesEditorPage", "Activate alignment", 0));
        label_20->setText(QApplication::translate("PreferencesEditorPage", "Cell size", 0));
        activateGridCheckBox->setText(QApplication::translate("PreferencesEditorPage", "Activate grid", 0));
        label_13->setText(QApplication::translate("PreferencesEditorPage", "Width", 0));
        showGridCheckBox->setText(QApplication::translate("PreferencesEditorPage", "Show grid", 0));
        showAlignmentCheckBox->setText(QApplication::translate("PreferencesEditorPage", "Show alignment", 0));
        label_14->setText(QApplication::translate("PreferencesEditorPage", "Node Elements", 0));
        label_15->setText(QApplication::translate("PreferencesEditorPage", "Drag area", 0));
        label_9->setText(QApplication::translate("PreferencesEditorPage", "Edge", 0));
        lineMode->clear();
        lineMode->insertItems(0, QStringList()
         << QApplication::translate("PreferencesEditorPage", "unset", 0)
         << QApplication::translate("PreferencesEditorPage", "broken", 0)
         << QApplication::translate("PreferencesEditorPage", "square", 0)
         << QApplication::translate("PreferencesEditorPage", "curve", 0)
        );
        label_10->setText(QApplication::translate("PreferencesEditorPage", "Line mode", 0));
        label_11->setText(QApplication::translate("PreferencesEditorPage", "Loop edges indent", 0));
        label_2->setText(QApplication::translate("PreferencesEditorPage", "Embedded Linkers", 0));
        label_3->setText(QApplication::translate("PreferencesEditorPage", "Size", 0));
        label_4->setText(QApplication::translate("PreferencesEditorPage", "Indent", 0));
        label_12->setText(QApplication::translate("PreferencesEditorPage", "Labels", 0));
        enableMoveLabelsCheckBox->setText(QApplication::translate("PreferencesEditorPage", "Enable move", 0));
        enableResizeLabelsCheckBox->setText(QApplication::translate("PreferencesEditorPage", "Enable resize", 0));
        labelDistanceLabel->setText(QApplication::translate("PreferencesEditorPage", "Label distance", 0));
        label_8->setText(QApplication::translate("PreferencesEditorPage", "Palette", 0));
        label_6->setText(QApplication::translate("PreferencesEditorPage", "   Representation   ", 0));
        label_7->setText(QApplication::translate("PreferencesEditorPage", "   Count of items in a row ", 0));
        paletteComboBox->clear();
        paletteComboBox->insertItems(0, QStringList()
         << QApplication::translate("PreferencesEditorPage", "Icons  and names", 0)
         << QApplication::translate("PreferencesEditorPage", "Icons", 0)
        );
        Q_UNUSED(PreferencesEditorPage);
    } // retranslateUi

};

namespace Ui {
    class PreferencesEditorPage: public Ui_PreferencesEditorPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORPAGE_H
