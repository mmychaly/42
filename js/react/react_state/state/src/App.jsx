import Counter from "./MyState.jsx"
import Changer from "./WordChange.jsx"
import ManyCounters from "./ManyCounters.jsx";
import InitialCounter from "./InitialCounter.jsx"

function App() {
    return (
      <>
        <h1 style={{textAlign:"Center"}}>Use state</h1>
        <Counter />
        <Changer />
        <ManyCounters />
        <Counter />
        <InitialCounter value={42} />
      </>
    );
}

export default App
