import { useState } from 'react'
import SendHello from './SendHello'
import SendOther from './SendOther'
import User from './User'
function App() {
  return (<>
            <SendOther />
            <SendHello />
            <User name='Mike' age='34'/>
          </>)
}

export default App
