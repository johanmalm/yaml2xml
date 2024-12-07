## Usage

    yaml2xml < rc.yaml

## Introduction

Convert YAML files to XML

For example, `foo: bar` in YAML is converted to `<foo>bar</foo>` in XML.

If rc.yaml includes a key-value pair where the value is an array, it is
converted to a sequence of `<key>array-element</key>` in XML.

For example, a YAML expression:

```
touch:
  - deviceName: xxxx
    mapToOutput: eDP-1
  - deviceName: yyyy
    mapToOutput: HDMI-1
```

is converted to an XML expression:

```
<touch>
  <deviceName>xxxx</deviceName>
  <mapToOutput>eDP-1</mapToOutput>
</touch>
<touch>
  <deviceName>yyyy</deviceName>
  <mapToOutput>eDP-1</mapToOutput>
</touch>
```

To avoid unnecessary indentations, some nodes that wrap array elements in XML
can be ommitted. This includes:

	- `<windowSwitcher><fields><field>`
    - `<regions><region>`
    - `<windowRules><windowRule>`
    - `<libinput><device>`
    - `<desktops><names><name>`

For example, window switcher can be configured like:

```
windowSwitcher:
  fields:
    - content: type
      width: 15%
    - content: title
      width: 85%
```

In addition, some specific keys in singular form with a sequence value in YAML
are converted to plural form in XML. This includes:

	- `keybinds` (converted to `keybind`)
    - `mousebinds` (converted to `mousebind`)
	- `actions` (converted to `action`)
	- `fonts` (converted to `font`)
	- `contexts` (converted to `context`)

For example, keybinds can be configured like:

```
keybinds:
  - { key: W-s, action: { name: Execute, command: foot } }
  - { key: W-a, action: { name: Execute, command: fuzzel } }
```

## Example:

rc.yaml:

```yaml
core:
  xwaylandPersistence: yes

placement:
  policy: cascade

theme:
  dropShadows: yes
  font:
    - place: ActiveWindow
      weight: normal
    - place: InactiveWindow
      weight: normal

windowSwitcher:
  show: yes
  fields:
    field:
      - content: type
        width: 15%
      - content: title
        width: 85%

regions:
  region:
    - { name: top-left, x: 0%, y: 0%, width: 50%, height: 50% }
    - { name: top-right, x: 50%, y: 0%, width: 50%, height: 50% }

keyboard:
  keybind:
    - key: A-F4
      action:
        - name: Close
    - key: W-s
      action:
        - name: Execute
          command: Alacritty
    - key: W-a
      action:
        - name: Execute
          command: fuzzel

mouse:
  default:
  context:
    - name: Frame
      mousebind:
        - button: W-Left
          event: Press # "action" is renamed to "event"
          action:
            - name: Raise
            - name: Move
        - button: W-Right
          event: Drag # "action" is renamed to "event"
          action:
            - name: Resize
        - button: A-Left
          event: Press # "action" is renamed to "event"
          # None
        - button: A-Left
          event: Press # "action" is renamed to "event"
          # None
        - button: A-Right
          event: Press # "action" is renamed to "event"
          # None
        - button: A-Right
          event: Press # "action" is renamed to "event"
          # None

libinput:
  device:
    - category: touchpad
      naturalScroll: yes
      tapAndDrag: no
```

rc.xml (formatted):

```xml
<?xml version="1.0"?>
<labwc_config>
  <core>
    <xwaylandPersistence>yes</xwaylandPersistence>
  </core>
  <placement>
    <policy>cascade</policy>
  </placement>
  <theme>
    <dropShadows>yes</dropShadows>
    <font>
      <place>ActiveWindow</place>
      <weight>normal</weight>
    </font>
    <font>
      <place>InactiveWindow</place>
      <weight>normal</weight>
    </font>
  </theme>
  <windowSwitcher>
    <show>yes</show>
    <fields>
      <field>
        <content>type</content>
        <width>15%</width>
      </field>
      <field>
        <content>title</content>
        <width>85%</width>
      </field>
    </fields>
  </windowSwitcher>
  <regions>
    <region>
      <name>top-left</name>
      <x>0%</x>
      <y>0%</y>
      <width>50%</width>
      <height>50%</height>
    </region>
    <region>
      <name>top-right</name>
      <x>50%</x>
      <y>0%</y>
      <width>50%</width>
      <height>50%</height>
    </region>
  </regions>
  <keyboard>
    <keybind>
      <key>A-F4</key>
      <action>
        <name>Close</name>
      </action>
    </keybind>
    <keybind>
      <key>W-s</key>
      <action>
        <name>Execute</name>
        <command>Alacritty</command>
      </action>
    </keybind>
    <keybind>
      <key>W-a</key>
      <action>
        <name>Execute</name>
        <command>fuzzel</command>
      </action>
    </keybind>
  </keyboard>
  <mouse>
    <default></default>
    <context>
      <name>Frame</name>
      <mousebind>
        <button>W-Left</button>
        <event>Press</event>
        <action>
          <name>Raise</name>
        </action>
        <action>
          <name>Move</name>
        </action>
      </mousebind>
      <mousebind>
        <button>W-Right</button>
        <event>Drag</event>
        <action>
          <name>Resize</name>
        </action>
      </mousebind>
      <mousebind>
        <button>A-Left</button>
        <event>Press</event>
      </mousebind>
      <mousebind>
        <button>A-Left</button>
        <event>Press</event>
      </mousebind>
      <mousebind>
        <button>A-Right</button>
        <event>Press</event>
      </mousebind>
      <mousebind>
        <button>A-Right</button>
        <event>Press</event>
      </mousebind>
    </context>
  </mouse>
  <libinput>
    <device>
      <category>touchpad</category>
      <naturalScroll>yes</naturalScroll>
      <tapAndDrag>no</tapAndDrag>
    </device>
  </libinput>
</labwc_config>
```





