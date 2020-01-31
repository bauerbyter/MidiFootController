//---------------------------------------------------------------------
#include "switch.h"

Switch::Switch(Button *button,
               Command command,
               byte ledPosition) : Control(button, command, ledPosition)
{
  //this->button = new Button(this->pin, DEBOUNCE_MS, INTERNAL_PULLUP, SWITCH_PULLUP);
}

bool Switch::changed()
{
  button->read();
  if (this->command.type == PC)
  {
    return button->wasPressed();
  }
  else if (this->command.type == CC || this->command.type == BANK)
  {
    if (button->wasPressed())
    {
      if (value == this->command.endValue)
      {
        this->value = this->command.startValue;
      }
      else
      {
        this->value = this->command.endValue;
      }
      return true;
    }
  }
  return false;
}
void Switch::updateValue(byte value)
{
  if (this->command.type == PC)
  {
    return;
  }

  if (value == this->command.endValue)
  {
    this->value = this->command.endValue;
  }
  else if (value == this->command.startValue)
  {
    this->value = this->command.startValue;
  }
}