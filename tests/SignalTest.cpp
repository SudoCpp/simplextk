#include "Signal.hpp"
#include "string.hpp"

static int effected = 0;

// class NoSupportSignals
// {
//     public:
//     simplex::Signal<> sig;
//     NoSupportSignals() : sig{this}{}
// };

// class SlotsWithoutSupport
// {
//     public:
//     void UpdatedEffected()
//     {
//         effected++;
//     }
// };

class SignallingClass
{
    public:
    simplex::Signal<> sig;
};

class SlotClass : public simplex::SupportsSignals
{
    public:
    void UpdatedEffected()
    {
        effected++;
    }
};

int main(int argc, char* argv[])
{
    std::string convert{argv[1]};
    //Won't work because It doesn't inherit SupportsSignals
    // if(convert == "-2")
    // {
    //     NoSupportSignals test{};
    // }
    //Static Assertion alerts why this is failing (this is good)
    // if(convert == "-1")
    // {
    //     SlotsWithoutSupport noSupport{};
    //     SignallingClass signalClass{};
    //     signalClass.sig.connect<SlotsWithoutSupport>(&SlotsWithoutSupport::UpdatedEffected, &noSupport);
    // }
    if(convert == "0")
    {
        SlotClass slotClass{};
        SignallingClass signalClass{};
        signalClass.sig.connect<SlotClass>(&SlotClass::UpdatedEffected, &slotClass);
        signalClass.sig.emit();
        if(effected == 1)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "1")
    {
        SlotClass* slotClass1 = new SlotClass{};
        SlotClass* slotClass2 = new SlotClass{};
        SignallingClass signalClass{};
        signalClass.sig.connect<SlotClass>(&SlotClass::UpdatedEffected, slotClass1);
        signalClass.sig.connect<SlotClass>(&SlotClass::UpdatedEffected, slotClass2);
        signalClass.sig.emit();
        if(effected == 2)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "2")
    {
        SlotClass* slotClass1 = new SlotClass{};
        SlotClass* slotClass2 = new SlotClass{};
        SignallingClass signalClass{};
        signalClass.sig.connect<SlotClass>(&SlotClass::UpdatedEffected, slotClass1);
        signalClass.sig.connect<SlotClass>(&SlotClass::UpdatedEffected, slotClass2);
        signalClass.sig.emit();
        signalClass.sig.emit();
        if(effected == 4)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "3")
    {
        SlotClass* slotClass1 = new SlotClass{};
        SlotClass* slotClass2 = new SlotClass{};
        SignallingClass signalClass{};
        signalClass.sig.connect<SlotClass>(&SlotClass::UpdatedEffected, slotClass1);
        signalClass.sig.connect<SlotClass>(&SlotClass::UpdatedEffected, slotClass2);
        signalClass.sig.emit();

        delete slotClass1;

        signalClass.sig.emit();
        if(effected == 3)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
}