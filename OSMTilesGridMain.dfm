object Main: TMain
  Left = 0
  Top = 0
  Caption = 'OSMTilesGrid'
  ClientHeight = 338
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    635
    338)
  PixelsPerInch = 96
  TextHeight = 17
  object gbLeftTop: TGroupBox
    Left = 8
    Top = 8
    Width = 281
    Height = 89
    Caption = 'Left-Top coord'
    TabOrder = 0
    object eLeftTopLat: TLabeledEdit
      Left = 16
      Top = 48
      Width = 121
      Height = 25
      EditLabel.Width = 17
      EditLabel.Height = 17
      EditLabel.Caption = 'Lat'
      TabOrder = 0
    end
    object eLeftTopLon: TLabeledEdit
      Left = 143
      Top = 48
      Width = 121
      Height = 25
      EditLabel.Width = 21
      EditLabel.Height = 17
      EditLabel.Caption = 'Lon'
      TabOrder = 1
    end
  end
  object gbRightBottom: TGroupBox
    Left = 8
    Top = 103
    Width = 281
    Height = 89
    Caption = 'Right-Bottom coord'
    TabOrder = 1
    object eRightBottomLat: TLabeledEdit
      Left = 16
      Top = 48
      Width = 121
      Height = 25
      EditLabel.Width = 17
      EditLabel.Height = 17
      EditLabel.Caption = 'Lat'
      TabOrder = 0
    end
    object eRightBottomLon: TLabeledEdit
      Left = 143
      Top = 48
      Width = 121
      Height = 25
      EditLabel.Width = 21
      EditLabel.Height = 17
      EditLabel.Caption = 'Lon'
      TabOrder = 1
    end
  end
  object gbZoom: TGroupBox
    Left = 8
    Top = 198
    Width = 153
    Height = 74
    Caption = 'Zoom'
    TabOrder = 2
    object eZoom: TEdit
      Left = 16
      Top = 32
      Width = 121
      Height = 25
      TabOrder = 0
      Text = '14'
    end
  end
  object mOutput: TMemo
    Left = 304
    Top = 16
    Width = 323
    Height = 312
    Anchors = [akLeft, akTop, akRight, akBottom]
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 3
    WordWrap = False
    ExplicitHeight = 280
  end
  object btnCalc: TButton
    Left = 192
    Top = 222
    Width = 80
    Height = 41
    Caption = 'Calc'
    TabOrder = 4
    OnClick = btnCalcClick
  end
  object btnSave: TButton
    Left = 8
    Top = 288
    Width = 96
    Height = 41
    Caption = 'Save to OSM'
    TabOrder = 5
    OnClick = btnSaveClick
  end
  object btnClose: TButton
    Left = 192
    Top = 288
    Width = 80
    Height = 41
    Caption = 'Close'
    TabOrder = 6
    OnClick = btnCloseClick
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'osm'
    Filter = '*.osm|*.osm|*.*|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 416
    Top = 96
  end
end
